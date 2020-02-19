#include "include/Heap.hpp"

Heap* Heap::_heap = NULL;

Heap::Heap(){}

Heap::~Heap(){
    free(this->_heap);
}

Heap* Heap::getInstance(){
    if (!_heap)
        _heap = new Heap();
    
    return _heap;
}

void Heap::setPath(std::string path){
    this->path = path + "/";
}

std::string Heap::getPath() const {
    return path;
}

void Heap::runMain(JavaClass *mainClass){
    JavaClassInstance* mainInstance = new JavaClassInstance();
    mainInstance->javaClass = mainClass;

    /* will search for a public method in the entrypoint class: "public void main(String[])"
    see: https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-5.html#jvms-5.2
    */
    u2 index;
    bool found_main_index = false;
    std::string method_name, method_descriptor;
    for(index = 0; index < mainClass->methods_count; index++){
        method_name = mainClass->getUtf8(mainClass->methods[index].name_index);
        method_descriptor = mainClass->getUtf8(mainClass->methods[index].type_index);
        if(
            method_name.compare("main") == 0 &&
            method_descriptor.compare("([Ljava/lang/String;)V") == 0 && 
            mainClass->isMethodAccessFlagSet(index, ACC_PUBLIC)
        ){
            found_main_index = true;
            break;
        }
    }

    // if the index containing the method is not found then the program exits
    if(!found_main_index){
        std::cout << "(E) Could not find the entrypoint method of " << mainClass->classFilePath << ". Terminating execution..." << std::endl;
        return;
    }

    // Caso exista um método "main", adiciona a classe ao unordered_map de instâncias.
    std::string key(mainClass->getUtf8(mainClass->constant_pool[mainClass->this_class-1].info.classInfo.name_index));
    key += ".class";
    _instantiatedClasses[key] = mainInstance;
    
    // Carrega os Fields associados à classe.
    addStaticFields(mainInstance);

    Frame *frame = new Frame(mainClass, mainClass->constant_pool, index, mainInstance);
    _executionFrames.push(frame);

    while(!_executionFrames.empty()){
        _executionFrames.top()->executeFrame();
    }
}

void Heap::pushFrame(Frame* frame){
    _executionFrames.push(frame);
}

void Heap::popFrame(){
    _executionFrames.pop();
}

JavaClass* Heap::getClass(std::string className){
    std::string basePath = getPath();
    std::string key = basePath + className + ".class";
    // std::cout << "getClass: " << key << std::endl;

    JavaClass *javaClass = _loadedClasses[key];
    if(javaClass == nullptr){
        javaClass = new JavaClass();
        javaClass->readClassFile(key);
        loadClass(javaClass);
    }

    return javaClass;
}

void Heap::loadClass(JavaClass *jc){
    std::string thisClass = jc->getUtf8(jc->constant_pool[jc->this_class-1].info.classInfo.name_index);
    thisClass += ".class";

    // std::cout << "loadClass: " << thisClass << std::endl;
    _loadedClasses[thisClass] = jc;

    JavaClassInstance *staticInstance;
    staticInstance = new JavaClassInstance();
    staticInstance->javaClass = jc;
    addStaticFields(staticInstance);
    _instantiatedClasses[thisClass] = staticInstance;
}

void Heap::addStaticFields(JavaClassInstance* _classInstance){
    _classInstance->fieldVariables = new std::unordered_map<std::string, Variable*>();
    JavaClass *javaClass = _classInstance->javaClass;
    std::string superClass, thisClass;
    u2 *superClassRef = &javaClass->constant_pool[javaClass->super_class-1].info.classInfo.name_index;
    u2 *thisClassRef  = &javaClass->constant_pool[javaClass->this_class-1].info.classInfo.name_index;

    do{
        superClass = javaClass->getUtf8(*superClassRef);
        thisClass  = javaClass->getUtf8(*thisClassRef);
        for(u2 i = 0; i < javaClass->fields_count; i++){
            // Apenas Fields com a flag "static";
            if(javaClass->fields[i].access_flags & 0x8){
                // std::cout << "Lendo o Field " << i+1 << " da classe " << thisClass << std::endl;
                int name_index = javaClass->fields[i].name_index;
                int type_index = javaClass->fields[i].type_index;
                std::string name(javaClass->getUtf8(name_index));
                std::string desc(javaClass->getUtf8(type_index));
                (*_classInstance->fieldVariables)[name] = new Variable(desc);
            }
        }
        if(superClass.compare("java/lang/Object") != 0){
            javaClass = Heap::getInstance()->getClass(superClass);
            break;
        }
    } while(superClass.compare("java/lang/Object") != 0);
}

void Heap::addInstanceFields(JavaClassInstance* _classInstance){
    _classInstance->fieldVariables = new std::unordered_map<std::string, Variable*>();
    JavaClass *javaClass = _classInstance->javaClass;
    std::string superClass, thisClass;
    u2 *superClassRef = &javaClass->constant_pool[javaClass->super_class-1].info.classInfo.name_index;
    u2 *thisClassRef  = &javaClass->constant_pool[javaClass->this_class-1].info.classInfo.name_index;

    do{
        superClass = javaClass->getUtf8(*superClassRef);
        thisClass  = javaClass->getUtf8(*thisClassRef);
        for(u2 i = 0; i < javaClass->fields_count; i++){
            int name_index = javaClass->fields[i].name_index;
            int type_index = javaClass->fields[i].type_index;
            std::string name(javaClass->getUtf8(name_index));
            std::string desc(javaClass->getUtf8(type_index));
            (*_classInstance->fieldVariables)[javaClass->getUtf8(name_index)] = new Variable(desc);
        }
        if(superClass.compare("java/lang/Object") != 0){
            javaClass = Heap::getInstance()->getClass(superClass);
            break;
        }
    } while(superClass.compare("java/lang/Object") != 0);
}

Frame* Heap::frameTop() {
    return _executionFrames.top();
}

JavaClassInstance* Heap::getInstantiatedClass(std::string cn) {
    std::size_t i = cn.rfind("/");
    std::string classPath(&cn[i + 1]);
    classPath += ".class";

    return _instantiatedClasses[classPath];
}

Variable* Heap::getStaticInfo(std::string cn, std::string fn) {
    std::string s(fn);
    std::size_t i = cn.rfind("/");
    std::string classPath(&cn[i + 1]);
    classPath += ".class";

    JavaClassInstance *javaClassInstance = _instantiatedClasses[classPath];

    return (*javaClassInstance->fieldVariables)[s];
}