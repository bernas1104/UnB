#include <limits>

#include "include/JavaClass.hpp"
#include "include/ClassPrinter.hpp"
#include "include/Heap.hpp"
#include "include/Frame.hpp"

#define APP_NAME "YAJVM"

#if defined(_WIN32) || defined(_WIN64)
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KNRM  "\x1B[0m"

std::unordered_map<u1, instructionInfo> mapInstructions;
int crz = 0;
void cruzeiro(){

	printf("%s                                                `-.                                                 \n", KYEL);
	printf("%s                                                `--`                                                \n", KYEL);
	printf("%s                                           `----::::---.`                                           \n", KYEL);
	printf("%s                                        `-------::::-------`                                        \n", KYEL);
	printf("%s                                  `..---:--.`   .::`   `---:--..``                                  \n", KYEL);
	printf("%s                               `-:::---::.      `::`      -::---:::-`                               \n", KYEL);
	printf("%s                              -:--.`  -:.       -::.       -:.  `.--:-                              \n", KYEL);
	printf("%s                             -:--`   `::-.   ` --  :. `   .-:-`   `-.:.                             \n", KYEL);
	printf("%s                            `:-:`    :-`.:``::-.:.-:`::: .:``:-    .-:-                             \n", KYEL);
	printf("%s                             -::-`--``-:::--:::-:::--:::--:::-`.-.`:::-                             \n", KYEL);
	printf("%s                              -:-`::-.-------.--:----..-------.-:-`-:.                              \n", KYEL);
	printf("%s                               `.-----::..---..........---.-::----..`                               \n", KYEL);
	printf("%s                                 `--...-::/+++++++++++++//::-...-.                                  \n", KYEL);
	printf("%s                                .-/+oo+/:----------````.---:/+oo+/-.                                \n", KBLU);
	printf("%s                           `-/+o+:-.-:`   `yyyyhhh+    oysso/:-`.-/+o+:.`                           \n", KBLU);
	printf("%s                        .:oo/-.--  :yh+    ..-ohh+`   .hhs/+os+    -..:+o+:`                        \n", KBLU);
	printf("%s                     `:oo:.`  /hh:  ohh:    :yhs-     +hhyyso/    +hy:  `./oo:`                     \n", KBLU);
	printf("%s                  `-+o/.`.`   `shy- `shy`  +hhhsoos- `yhh////-   /hh+`  `:/../o+-                   \n", KBLU);
	printf("%s                `:o+-.:oyyy/   .yhy::shy.  /++///::. `+oosyyy:  /hho`  .ohhyo-.-oo-`                \n", KBLU);
	printf("%s              `:s+../yho:ohy:.  .oyyso/.`.-::/+++oo+++/::--.-` -yho` `/yhy::shs. -+o-               \n", KBLU);
	printf("%s             -o+.  .shh++yyshy+`  `.-/+syyhhhhhhhhhhhhhhhhyys+:-.-` .shyoys+shy-   -oo-             \n", KBLU);
	printf("%s           .+o-     `/yhho``:+:`./oyhhhhhhhhhhhhhhhhhhhhhhhhhhhyyo:../o- .yhs:.      :s+`           \n", KBLU);
	printf("%s          :s/`.:/:`   .ohh/  ./syhhhhhhhhhhhhhhhhoshhhhhhhhhhhhhhhhyo:.  +hy-  `.://:.`+s-          \n", KBLU);
	printf("%s        `/s-`+yys+``:` `::.-oyhhhhhhhhhhhhhhhhhhy`.hhhhhhhhhhhhhhhhhhhy+..:-  -syhysyy/`:s:         \n", KBLU);
	printf("%s       `oo` +hy.` `oho`  -ohhhhhhhhhhhhhhhhhyo:-.  .-:ohhhhhhhhhhhhhhhhhy+.  .yho-``-hh: .s+        \n", KBLU);
	printf("%s      `oo`  /hh+-..oho .+yhhhhhhhhhhhhhhhhhhhhy/    +yhhhhhhhhhhhhhhhhhhhhy/``yh+..-ohh-  .s+       \n", KBLU);
	printf("%s     `oo`    :syhyyy+.:yhhhhhhhhhhhhhhhhhhhhhhh--++-:hhhhhhhhhhhhhhhhhhhhhhhs-.oyyyhyo-    `s+      \n", KBLU);
	printf("%s     +s`      `.---.`/hhhhhhhhhhhhhhhhhhhhhhhhyshhhhsyhhhhhhhhhhhhhhhhhhhhhhhy:`.---.       .y:     \n", KBLU);
	printf("%s    -y.            `+hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh/             :y.    \n", KBLU);
	printf("%s   `y/             +hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh:             oo    \n", KBLU);
	printf("%s   :y`            :hhhhhhhhhhhhohhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhshhhhhhhhhhhy-            .h-   \n", KBLU);
	printf("%s   y/            .yhhhhhhhhhhhs`+hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhy.ohhhhhhhhhhhs`            oo   \n", KBLU);
	printf("%s  -h. +//:::--.` /hhhhhhhhy+::. `::/shhhhhhhhhhhhhhhhhhhhhhhhhhyo++- ./++shhhhhhhh: `.. `.`.// -h`  \n", KBLU);
	printf("%s  /y .hhyhhhhhy.`shhhhhhhhhyo.   `+yhhhhhhhhhhhhhhhhhhhhhhhhhhhhy+.    :shhhhhhhhho -yy.+y/:hh``h-  \n", KBLU);
	printf("%s  oo -hh.sh/+hy`.hhhhhhhhhhhy../-`ohhhhhhhhhhhhhhhhhhhhshhhhhhhhhy.`-.`ohhhhhhhhhhy`.yh-+ho-hh. y/  \n", KBLU);
	printf("%s  s+ /hy`yh-+ho -hhhhhhhhhhhsshhhsohhhhhhhhhhhhhhhhhyyo.yyyhhhhhho+yhyo+hhhhhhhhhhy.`yhsyhhyhh- s+  \n", KBLU);
	printf("%s  s+ .:- .-`:+: -hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhyo-` `:ohhhhhhhhhhhhhhhhhhhhhhhh. +o+++///:. s+  \n", KBLU);
	printf("%s  oo       ```  .hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh/.:.ohhhhhhhhhhhhhhhhhhhhhhhhy`  `         y+  \n", KBLU);
	printf("%s  +s  .++ /yyy+``yhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhoyhyshhhhhhhhhhhhhhhhhhhhhhhhs `/oo::++:  `h:  \n", KBLU);
	printf("%s  -h` sho.yh++h+ ohhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh/ /hsohyshh/ .h.  \n", KBLU);
	printf("%s  `h: sh::hh-oh+ -hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhy.`yh/:h/`sh: +s   \n", KBLU);
	printf("%s   +s .syhyo`//`  +hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh/ :yyyhhyshy``y:   \n", KBLU);
	printf("%s   .h- `.-.   `.:``shhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhho ```.-::+os/ /y`   \n", KBLU);
	printf("%s    /y`   `.:oyhhs`.shhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhho`.oo/.`      .y:    \n", KBLU);
	printf("%s    `so `+yhhhs:ohs`.shhhhhhhhhhhhhhhhhhhhhhhhhhhhyhhhhhhhhhhhhhhhhhhhhhhhhhhho` .+yhhs+-   `s+     \n", KBLU);
	printf("%s     `y/ :o::yy:/hh: `+hhhhhhhhhhhhhhhhhhhhhhhhhhh.+hhhhhhhhhhhhhhhhhhhhhhhhh/`-:.` ./shh:  os`     \n", KBLU);
	printf("%s      .y/    -syys/`   :yhhhhhhhhhhhhhhhhhhhhyo++: `+++shhhhhhhhhhhhhhhhhhhs- .shhs+-`-hh: +s`      \n", KBLU);
	printf("%s       .y/     ``  .-:-``+yhhhhhhhhhhhhhhhhhhhy+.    :shhhhhhhhhhhhhhhhhhy/`   `-/syhyhy:`+s`       \n", KBLU);
	printf("%s        .s+`     -ohhyyyo..+yhhhhhhhhhhhhhhhhhhh.`-.`ohhhhhhhhhhhhhhhhhy/``        .-:-`.oo`        \n", KBLU);
	printf("%s         `+s.   -hho-``ohy` `:shhhhhhhhhhhhhhhho+yhho/hhhhhhhhhhhhhhyo:`.+s/`          -s/          \n", KBLU);
	printf("%s           :s/` /hh- `-shy`  ``./syhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhyo:.   `+yhy/``-ss. `+s-           \n", KBLU);
	printf("%s            `+s-`+yysshhs-  -yyo:..-/syhhhhhhhhhhhhhhhhhhhhhyyo/-.-+oo+-  .+yhyshs:`:s/`            \n", KBLU);
	printf("%s              .oo-.://:.   :yhs+yhs:  `.-/+ossyyyyyyyyso+/:-`   .shs/oo:`   .+ys:`:s+.              \n", KBLU);
	printf("%s                -oo:`     :hhho::yhy` +so+/:-.` `.......        /hh-   -++    `.:s+.                \n", KBLU);
	printf("%s                  .+s/.  :hho-/yhy+.  -:shhyyy` +yhyyyyy        .yhy:`-yho   .+s/.                  \n", KBLU);
	printf("%s                    `:oo:.-:` .yho     `shy```  +hh+///:         .+yhhys/`./oo-`                    \n", KBLU);
	printf("%s                       `:oo/-`-+s.     :hh+     :hhysoo/           `...-+o+:`                       \n", KBLU);
	printf("%s                          `-+oo/-`     ohh.     -hhsooos:         .:+oo/-`                          \n", KBLU);
	printf("%s                              `./+oo+/-...      `+++////-  `.:/+oo+:.`                              \n", KBLU);
	printf("%s                                    `-:/+oooooo++++++oooooo+/:.`                                    \n", KBLU);
	printf("%s                                               ````                                                \n", KBLU);
	printf("%s                          Cruzeiro Campeão da Copa do Brasil 2018\n", KNRM);
	return;
}

int get_opt(){
    int opt;
    if(crz){
        system(CLEAR);
    } else {
        crz++;
    }
    std::cout << "/**************************\\" << std::endl;
    std::cout << "|----------SBJVM-----------|" << std::endl;
    std::cout << "|**************************|" << std::endl;
    std::cout << "|1 - Bytecode Viewer       |" << std::endl;
    std::cout << "|                          |" << std::endl;
    std::cout << "|2 - Executar programa     |" << std::endl;
    std::cout << "|                          |" << std::endl;
    std::cout << "|3 - Sair                  |" << std::endl;
    std::cout << "\\**************************/" << std::endl;
    std::cin >> opt;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return opt;
}

int run_jvm(int opt, std::string class_file_loc){
    JavaClass *cl;
    ClassPrinter *cp;

    cl = new JavaClass();
    if(cl->readClassFile(class_file_loc)){
        switch(opt){
            case 1:
                cp = new ClassPrinter();
                cp->setClass(*cl);
                cp->printConstPool();
                cp->printClassFile();
                delete(cp);
                break;
            case 2:
                system(CLEAR);
                Frame::setOpcodes();
                Heap *hp;
                hp = Heap::getInstance();
                hp->runMain(cl);
                break;
            case 3:
                std::cout << "Encerrando a JVM...\n";
                break;
            default:
                std::cout << "Opcao invalida!\n";
        }
    }
    cl->deleteBytecode();
    if(cl->constant_pool != NULL)
        cl->deleteConstantPool();
    cl->deleteClassInfo();
    delete(cl);

    return 0;
}

int main(const int argc, const char* argv[]){
    int opt = 0, i;
    std::string stop, path;
    std::size_t found;

    bool batch_processing = false;

    std::string class_file_loc = std::string(argv[1]);
    found = class_file_loc.find('/');
    if(found != std::string::npos){
        for(i = class_file_loc.size() - 1; i >= 0; i--){
            if(class_file_loc[i] == '/')
                break;
        }
        path = class_file_loc.substr(0, i);
        Heap::getInstance()->setPath(path);
    }
    if (argc >= 3){
        opt = std::stoi(argv[2]);
        batch_processing = true;
    }

    setAssemblyMap();

    if (!batch_processing){
        cruzeiro();
        while(opt != 3){
            opt = get_opt();
            run_jvm(opt, class_file_loc);
            std::cout << "Pressione ENTER para continuar...\n";
            getchar();
        }
    } else {
        run_jvm(opt, class_file_loc);
    }        

    return 0;
}

/** \mainpage
 *  hello!
 */