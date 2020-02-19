#pragma once
#include "Types.hpp"

#include <unordered_map>

//! Struct de informações das instruções Java assembly.
/*!
    A struct instructInfo é responsável por armazenar o mneumonico e a quantidade de
    argumentos necessária para cada uma das 201 instruções existentes.
    As structs serão posteriormente mapeadas por um std::unordered_map com base no 
    hexadecimal que a identifica.
 */
struct instructionInfo {
    std::string name;                                           //!< Armazena o mneumonico, em formato std::string, da instrução.
    int args;                                                   //!< Armazena o número de argumentos da instrução.
};

extern std::unordered_map<u1, instructionInfo> mapInstructions; //!< std::unordered_map que armazena o mapeamento das instruções do Java assembly.

//! Método responsável por montar o mapeamento das instruções Java assembly.
/*!
    O método declara uma estrutura para cada uma das 201 instruções do Java assembly,
    define um nome, em formato std::string, e uma quantidade de argumentos e depois
    insere a struct no std::unordered_map mapInstructions.
 */
inline void setAssemblyMap() {
    instructionInfo aaload;
    aaload.name = "aaload"; aaload.args = 0;
    mapInstructions.insert({0x32, aaload});

    instructionInfo aastore;
    aastore.name = "aastore"; aastore.args = 0;
    mapInstructions.insert({0x53, aastore});

    instructionInfo aconst_null;
    aconst_null.name ="aconst_null"; aconst_null.args = 0;
    mapInstructions.insert({0x01, aconst_null});

    instructionInfo aload;
    aload.name = "aload"; aload.args = 1;
    mapInstructions.insert({0x19, aload});

    instructionInfo aload_0;
    aload_0.name = "aload_0"; aload_0.args = 0;
    mapInstructions.insert({0x2a, aload_0});

    instructionInfo aload_1;
    aload_1.name = "aload_1"; aload_1.args = 0;
    mapInstructions.insert({0x2b, aload_1});

    instructionInfo aload_2;
    aload_2.name = "aload_2"; aload_2.args = 0;
    mapInstructions.insert({0x2c, aload_2});

    instructionInfo aload_3;
    aload_3.name = "aload_3"; aload_3.args = 0;
    mapInstructions.insert({0x2d, aload_3});

    instructionInfo anewarray;
    anewarray.name = "anewarray"; anewarray.args = 2;
    mapInstructions.insert({0xbd, anewarray});

    instructionInfo areturn;
    areturn.name = "areturn"; areturn.args = 0;
    mapInstructions.insert({0xb0, areturn});

    instructionInfo arraylength;
    arraylength.name = "arraylength"; arraylength.args = 0;
    mapInstructions.insert({0xbe, arraylength});

    instructionInfo astore;
    astore.name = "astore"; astore.args = 1;
    mapInstructions.insert({0x3a, astore});

    instructionInfo astore_0;
    astore_0.name = "astore_0"; astore_0.args = 0;
    mapInstructions.insert({0x4b, astore_0});

    instructionInfo astore_1;
    astore_1.name = "astore_1"; astore_1.args = 0;
    mapInstructions.insert({0x4c, astore_1});

    instructionInfo astore_2;
    astore_2.name = "astore_2"; astore_2.args = 0;
    mapInstructions.insert({0x4d, astore_2});

    instructionInfo astore_3;
    astore_3.name = "astore_3"; astore_3.args = 0;
    mapInstructions.insert({0x4e, astore_3});
    
    instructionInfo athrow;
    athrow.name = "athrow"; athrow.args = 0;
    mapInstructions.insert({0xbf, athrow});

    instructionInfo baload;
    baload.name = "baload"; baload.args = 0;
    mapInstructions.insert({0x33, baload});

    instructionInfo bastore;
    bastore.name = "bastore"; bastore.args = 0;
    mapInstructions.insert({0x54, bastore});

    instructionInfo bipush;
    bipush.name = "bipush"; bipush.args = 1;
    mapInstructions.insert({0x10, bipush});

    instructionInfo caload;
    caload.name = "caload"; caload.args = 0;
    mapInstructions.insert({0x34, caload});

    instructionInfo castore;
    castore.name = "castore"; castore.args = 0;
    mapInstructions.insert({0x55, castore});

    instructionInfo checkcast;
    checkcast.name = "checkcast"; checkcast.args = 2;
    mapInstructions.insert({0xc0, checkcast});

    instructionInfo d2f;
    d2f.name = "d2f"; d2f.args = 0;
    mapInstructions.insert({0x90, d2f});

    instructionInfo d2i;
    d2i.name = "d2i"; d2i.args = 0;
    mapInstructions.insert({0x8e, d2i});

    instructionInfo d2l;
    d2l.name = "d2l"; d2l.args = 0;
    mapInstructions.insert({0x8f, d2l});

    instructionInfo dadd;
    dadd.name = "dadd"; dadd.args = 0;
    mapInstructions.insert({0x63, dadd});

    instructionInfo daload;
    daload.name = "daload"; daload.args = 0;
    mapInstructions.insert({0x31, daload});

    instructionInfo dastore;
    dastore.name = "dastore"; dastore.args = 0;
    mapInstructions.insert({0x52, dastore});

    instructionInfo dcmpg;
    dcmpg.name = "dcmpg"; dcmpg.args = 0;
    mapInstructions.insert({0x98, dcmpg});

    instructionInfo dcmpl;
    dcmpl.name = "dcmpl"; dcmpl.args = 0;
    mapInstructions.insert({0x97, dcmpl});

    instructionInfo dconst_0;
    dconst_0.name = "dconst_0"; dconst_0.args = 0;
    mapInstructions.insert({0x0e, dconst_0});

    instructionInfo dconst_1;
    dconst_1.name = "dconst_1"; dconst_1.args = 0;
    mapInstructions.insert({0x0f, dconst_1});

    instructionInfo ddiv;
    ddiv.name = "ddiv"; ddiv.args = 0;
    mapInstructions.insert({0x6f, ddiv});

    instructionInfo dload;
    dload.name = "dload"; dload.args = 1;
    mapInstructions.insert({0x18, dload});

    instructionInfo dload_0;
    dload_0.name = "dload_0"; dload_0.args = 0;
    mapInstructions.insert({0x26, dload_0});

    instructionInfo dload_1;
    dload_1.name = "dload_1"; dload_1.args = 0;
    mapInstructions.insert({0x27, dload_1});

    instructionInfo dload_2;
    dload_2.name = "dload_2"; dload_2.args = 0;
    mapInstructions.insert({0x28, dload_2});

    instructionInfo dload_3;
    dload_3.name = "dload_3"; dload_3.args = 0;
    mapInstructions.insert({0x29, dload_3});

    instructionInfo dmul;
    dmul.name = "dmul"; dmul.args = 0;
    mapInstructions.insert({0x6b, dmul});

    instructionInfo dneg;
    dneg.name = "dneg"; dneg.args = 0;
    mapInstructions.insert({0x77, dneg});

    instructionInfo drem;
    drem.name = "drem"; drem.args = 0;
    mapInstructions.insert({0x73, drem});

    instructionInfo dreturn;
    dreturn.name = "dreturn"; dreturn.args = 0;
    mapInstructions.insert({0xaf, dreturn});

    instructionInfo dstore;
    dstore.name = "dstore"; dstore.args = 1;
    mapInstructions.insert({0x39, dstore});

    instructionInfo dstore_0;
    dstore_0.name = "dstore_0"; dstore_0.args = 0;
    mapInstructions.insert({0x47, dstore_0});

    instructionInfo dstore_1;
    dstore_1.name = "dstore_1"; dstore_1.args = 0;
    mapInstructions.insert({0x48, dstore_1});

    instructionInfo dstore_2;
    dstore_2.name = "dstore_2"; dstore_2.args = 0;
    mapInstructions.insert({0x49, dstore_2});

    instructionInfo dstore_3;
    dstore_3.name = "dstore_3"; dstore_3.args = 0;
    mapInstructions.insert({0x4a, dstore_3});

    instructionInfo dsub;
    dsub.name = "dsub"; dsub.args = 0;
    mapInstructions.insert({0x67, dsub});

    instructionInfo dup;
    dup.name = "dup"; dup.args = 0;
    mapInstructions.insert({0x59, dup});

    instructionInfo dup_x1;
    dup_x1.name = "dup_x1"; dup_x1.args = 0;
    mapInstructions.insert({0x5a, dup_x1});

    instructionInfo dup_x2;
    dup_x2.name = "dup_x2"; dup_x2.args = 0;
    mapInstructions.insert({0x5b, dup_x2});

    instructionInfo dup2;
    dup2.name = "dup2"; dup2.args = 0;
    mapInstructions.insert({0x5c, dup2});

    instructionInfo dup2_x1;
    dup2_x1.name = "dup2_x1"; dup2_x1.args = 0;
    mapInstructions.insert({0x5d, dup2_x1});

    instructionInfo dup2_x2;
    dup2_x2.name = "dup2_x2"; dup2_x2.args = 0;
    mapInstructions.insert({0x5e, dup2_x2});

    instructionInfo f2d;
    f2d.name = "f2d"; f2d.args = 0;
    mapInstructions.insert({0x8d, f2d});

    instructionInfo f2i;
    f2i.name = "f2i"; f2i.args = 0;
    mapInstructions.insert({0x8b, f2i});

    instructionInfo f2l;
    f2l.name = "f2l"; f2l.args = 0;
    mapInstructions.insert({0x8c, f2l});

    instructionInfo fadd;
    fadd.name = "fadd"; fadd.args = 0;
    mapInstructions.insert({0x62, fadd});

    instructionInfo faload;
    faload.name = "faload"; faload.args = 0;
    mapInstructions.insert({0x30, faload});

    instructionInfo fastore;
    fastore.name = "fastore"; fastore.args = 0;
    mapInstructions.insert({0x51, fastore});

    instructionInfo fcmpg;
    fcmpg.name = "fcmpg"; fcmpg.args = 0;
    mapInstructions.insert({0x96, fcmpg});

    instructionInfo fcmpl;
    fcmpl.name = "fcmpl"; fcmpl.args = 0;
    mapInstructions.insert({0x95, fcmpl});

    instructionInfo fconst_0;
    fconst_0.name = "fconst_0"; fconst_0.args = 0;
    mapInstructions.insert({0x0b, fconst_0});

    instructionInfo fconst_1;
    fconst_1.name = "fconst_1"; fconst_1.args = 0;
    mapInstructions.insert({0x0c, fconst_1});

    instructionInfo fconst_2;
    fconst_2.name = "fconst_2"; fconst_2.args = 0;
    mapInstructions.insert({0x0d, fconst_2});

    instructionInfo fdiv;
    fdiv.name = "fdiv"; fdiv.args = 0;
    mapInstructions.insert({0x6e, fdiv});
    
    instructionInfo fload;
    fload.name = "fload"; fload.args = 1;
    mapInstructions.insert({0x17, fload});

    instructionInfo fload_0;
    fload_0.name = "fload_0"; fload_0.args = 0;
    mapInstructions.insert({0x22, fload_0});

    instructionInfo fload_1;
    fload_1.name = "fload_1"; fload_1.args = 0;
    mapInstructions.insert({0x23, fload_1});

    instructionInfo fload_2;
    fload_2.name = "fload_2"; fload_2.args = 0;
    mapInstructions.insert({0x24, fload_2});

    instructionInfo fload_3;
    fload_3.name = "fload_3"; fload_3.args = 0;
    mapInstructions.insert({0x25, fload_3});

    instructionInfo fmul;
    fmul.name = "fmul"; fmul.args = 0;
    mapInstructions.insert({0x6a, fmul});

    instructionInfo fneg;
    fneg.name = "fneg"; fneg.args = 0;
    mapInstructions.insert({0x76, fneg});

    instructionInfo frem;
    frem.name = "frem"; frem.args = 0;
    mapInstructions.insert({0x72, frem});

    instructionInfo freturn;
    freturn.name = "freturn"; freturn.args = 0;
    mapInstructions.insert({0xae, freturn});

    instructionInfo fstore;
    fstore.name = "fstore"; fstore.args = 1;
    mapInstructions.insert({0x38, fstore});

    instructionInfo fstore_0;
    fstore_0.name = "fstore_0"; fstore_0.args = 0;
    mapInstructions.insert({0x43, fstore_0});

    instructionInfo fstore_1;
    fstore_1.name = "fstore_1"; fstore_1.args = 0;
    mapInstructions.insert({0x44, fstore_1});

    instructionInfo fstore_2;
    fstore_2.name = "fstore_2"; fstore_2.args = 0;
    mapInstructions.insert({0x45, fstore_2});

    instructionInfo fstore_3;
    fstore_3.name = "fstore_3"; fstore_3.args = 0;
    mapInstructions.insert({0x46, fstore_3});

    instructionInfo fsub;
    fsub.name = "fsub"; fsub.args = 0;
    mapInstructions.insert({0x66, fsub});

    instructionInfo getfield;
    getfield.name = "getfield\t"; getfield.args = 2;
    mapInstructions.insert({0xb4, getfield});

    instructionInfo getstatic;
    getstatic.name = "getstatic"; getstatic.args = 2;
    mapInstructions.insert({0xb2, getstatic});

    instructionInfo jGoto;
    jGoto.name = "goto"; jGoto.args = 2;
    mapInstructions.insert({0xa7, jGoto});

    instructionInfo jGoto_w;
    jGoto_w.name = "goto_w"; jGoto_w.args = 4;
    mapInstructions.insert({0xc8, jGoto_w});

    instructionInfo i2b;
    i2b.name = "i2b"; i2b.args = 0;
    mapInstructions.insert({0x91, i2b});

    instructionInfo i2c;
    i2c.name = "i2c"; i2c.args = 0;
    mapInstructions.insert({0x92, i2c});

    instructionInfo i2d;
    i2d.name = "i2d"; i2d.args = 0;
    mapInstructions.insert({0x87, i2d});

    instructionInfo i2f;
    i2f.name = "i2f"; i2f.args = 0;
    mapInstructions.insert({0x86, i2f});

    instructionInfo i2l;
    i2l.name = "i2l"; i2l.args = 0;
    mapInstructions.insert({0x85, i2l});

    instructionInfo i2s;
    i2s.name = "i2s"; i2s.args = 0;
    mapInstructions.insert({0x93, i2s});

    instructionInfo iadd;
    iadd.name = "iadd"; iadd.args = 0;
    mapInstructions.insert({0x60, iadd});

    instructionInfo iaload;
    iaload.name = "iaload"; iaload.args = 0;
    mapInstructions.insert({0x2e, iaload});

    instructionInfo iand;
    iand.name = "iand"; iand.args = 0;
    mapInstructions.insert({0x73, iand});

    instructionInfo iastore;
    iastore.name = "iastore"; iastore.args = 0;
    mapInstructions.insert({0x4f, iastore});

    instructionInfo iconst_m1;
    iconst_m1.name = "iconst_m1"; iconst_m1.args = 0;
    mapInstructions.insert({0x02, iconst_m1});

    instructionInfo iconst_0;
    iconst_0.name = "iconst_0"; iconst_0.args = 0;
    mapInstructions.insert({0x03, iconst_0});

    instructionInfo iconst_1;
    iconst_1.name = "iconst_1"; iconst_1.args = 0;
    mapInstructions.insert({0x04, iconst_1});

    instructionInfo iconst_2;
    iconst_2.name = "iconst_2"; iconst_2.args = 0;
    mapInstructions.insert({0x05, iconst_2});

    instructionInfo iconst_3;
    iconst_3.name = "iconst_3"; iconst_3.args = 0;
    mapInstructions.insert({0x06, iconst_3});

    instructionInfo iconst_4;
    iconst_4.name = "iconst_4"; iconst_4.args = 0;
    mapInstructions.insert({0x07, iconst_4});

    instructionInfo iconst_5;
    iconst_5.name = "iconst_5"; iconst_5.args = 0;
    mapInstructions.insert({0x08, iconst_5});

    instructionInfo idiv;
    idiv.name = "idiv"; idiv.args = 0;
    mapInstructions.insert({0x6c, idiv});

    instructionInfo if_acmpeq;
    if_acmpeq.name = "if_acmpeq"; if_acmpeq.args = 2;
    mapInstructions.insert({0xa5, if_acmpeq});

    instructionInfo if_acmpne;
    if_acmpne.name = "if_acmpne"; if_acmpne.args = 2;
    mapInstructions.insert({0xa6, if_acmpne});

    instructionInfo if_icmpeq;
    if_icmpeq.name = "if_icmpeq"; if_icmpeq.args = 2;
    mapInstructions.insert({0x9f, if_icmpeq});

    instructionInfo if_icmpne;
    if_icmpne.name = "if_icmpne"; if_icmpne.args = 2;
    mapInstructions.insert({0xa0, if_icmpne});

    instructionInfo if_icmplt;
    if_icmplt.name = "if_icmplt"; if_icmplt.args = 2;
    mapInstructions.insert({0xa1, if_icmplt});

    instructionInfo if_icmpge;
    if_icmpge.name = "if_icmpge"; if_icmpge.args = 2;
    mapInstructions.insert({0xa2, if_icmpge});

    instructionInfo if_icmpgt;
    if_icmpgt.name = "if_icmpgt"; if_icmpgt.args = 2;
    mapInstructions.insert({0xa3, if_icmpgt});

    instructionInfo if_icmple;
    if_icmple.name = "if_icmple"; if_icmple.args = 2;
    mapInstructions.insert({0xa4, if_icmple});

    instructionInfo ifeq;
    ifeq.name = "ifeq"; ifeq.args = 2;
    mapInstructions.insert({0x99, ifeq});

    instructionInfo ifne;
    ifne.name = "ifne"; ifne.args = 2;
    mapInstructions.insert({0x9a, ifne});

    instructionInfo iflt;
    iflt.name = "iflt"; iflt.args = 2;
    mapInstructions.insert({0x9b, iflt});

    instructionInfo ifge;
    ifge.name = "ifge"; ifge.args = 2;
    mapInstructions.insert({0x9c, ifge});

    instructionInfo ifgt;
    ifgt.name = "ifgt"; ifgt.args = 2;
    mapInstructions.insert({0x9d, ifgt});
    
    instructionInfo ifle;
    ifle.name = "ifle"; ifle.args = 2;
    mapInstructions.insert({0x9e, ifle});

    instructionInfo ifnonnull;
    ifnonnull.name = "ifnonnull"; ifnonnull.args = 2;
    mapInstructions.insert({0xc7, ifnonnull});

    instructionInfo ifnull;
    ifnull.name = "ifnull"; ifnull.args = 2;
    mapInstructions.insert({0xc6, ifnull});

    instructionInfo iinc;
    iinc.name = "iinc"; iinc.args = 2;
    mapInstructions.insert({0x84, iinc});

    instructionInfo iload;
    iload.name = "iload"; iload.args = 1;
    mapInstructions.insert({0x15, iload});

    instructionInfo iload_0;
    iload_0.name = "iload_0"; iload_0.args = 0;
    mapInstructions.insert({0x1a, iload_0});

    instructionInfo iload_1;
    iload_1.name = "iload_1"; iload_1.args = 0;
    mapInstructions.insert({0x1b, iload_1});

    instructionInfo iload_2;
    iload_2.name = "iload_2"; iload_2.args = 0;
    mapInstructions.insert({0x1c, iload_2});

    instructionInfo iload_3;
    iload_3.name = "iload_3"; iload_3.args = 0;
    mapInstructions.insert({0x1d, iload_3});

    instructionInfo imul;
    imul.name = "imul"; imul.args = 0;
    mapInstructions.insert({0x68, imul});

    instructionInfo ineg;
    ineg.name = "ineg"; ineg.args = 0;
    mapInstructions.insert({0x74, ineg});

    instructionInfo instanceof;
    instanceof.name = "instanceof"; instanceof.args = 2;
    mapInstructions.insert({0xc1, instanceof});

    instructionInfo invokedynamic;
    invokedynamic.name = "invokedynamic"; invokedynamic.args = 4;
    mapInstructions.insert({0xba, invokedynamic});

    instructionInfo invokeinterface;
    invokeinterface.name = "invokeinterface"; invokeinterface.args = 4;
    mapInstructions.insert({0xb9, invokeinterface});

    instructionInfo invokespecial;
    invokespecial.name = "invokespecial"; invokespecial.args = 2;
    mapInstructions.insert({0xb7, invokespecial});

    instructionInfo invokestatic;
    invokestatic.name = "invokestatic"; invokestatic.args = 2;
    mapInstructions.insert({0xb8, invokestatic});

    instructionInfo invokevirtual;
    invokevirtual.name = "invokevirtual"; invokevirtual.args = 2;
    mapInstructions.insert({0xb6, invokevirtual});

    instructionInfo ior;
    ior.name = "ior"; ior.args = 0;
    mapInstructions.insert({0x80, ior});

    instructionInfo irem;
    irem.name = "irem"; irem.args = 0;
    mapInstructions.insert({0x70, irem});

    instructionInfo ireturn;
    ireturn.name = "ireturn"; ireturn.args = 0;
    mapInstructions.insert({0xac, ireturn});

    instructionInfo ishl;
    ishl.name = "ishl"; ishl.args = 0;
    mapInstructions.insert({0x78, ishl});

    instructionInfo ishr;
    ishr.name = "ishr"; ishr.args = 0;
    mapInstructions.insert({0x7a, ishr});

    instructionInfo istore;
    istore.name = "istore"; istore.args = 1;
    mapInstructions.insert({0x36, istore});

    instructionInfo istore_0;
    istore_0.name = "istore_0"; istore_0.args = 0;
    mapInstructions.insert({0x3b, istore_0});

    instructionInfo istore_1;
    istore_1.name = "istore_1"; istore_1.args = 0;
    mapInstructions.insert({0x3c, istore_1});

    instructionInfo istore_2;
    istore_2.name = "istore_2"; istore_2.args = 0;
    mapInstructions.insert({0x3d, istore_2});

    instructionInfo istore_3;
    istore_3.name = "istore_3"; istore_3.args = 0;
    mapInstructions.insert({0x3e, istore_3});

    instructionInfo isub;
    isub.name = "isub"; isub.args = 0;
    mapInstructions.insert({0x64, isub});

    instructionInfo iushr;
    iushr.name = "iushr"; iushr.args = 0;
    mapInstructions.insert({0x7c, iushr});

    instructionInfo ixor;
    ixor.name = "ixor"; ixor.args = 0;
    mapInstructions.insert({0x82, ixor});

    instructionInfo jsr;
    jsr.name = "jsr"; jsr.args = 2;
    mapInstructions.insert({0xa8, jsr});

    instructionInfo jsr_w;
    jsr_w.name = "jsr_w"; jsr_w.args = 4;
    mapInstructions.insert({0xc9, jsr_w});

    instructionInfo l2d;
    l2d.name = "l2d"; l2d.args = 0;
    mapInstructions.insert({0x8a, l2d});
    
    instructionInfo l2f;
    l2f.name = "l2f"; l2f.args = 0;
    mapInstructions.insert({0x89, l2f});

    instructionInfo l2i;
    l2i.name = "l2i"; l2i.args = 0;
    mapInstructions.insert({0x88, l2i});

    instructionInfo ladd;
    ladd.name = "ladd"; ladd.args = 0;
    mapInstructions.insert({0x61, ladd});

    instructionInfo laload;
    laload.name = "laload"; laload.args = 0;
    mapInstructions.insert({0x2f, laload});

    instructionInfo land;
    land.name = "land"; land.args = 0;
    mapInstructions.insert({0x7f, land});

    instructionInfo lastore;
    lastore.name = "lastore"; lastore.args = 0;
    mapInstructions.insert({0x50, lastore});

    instructionInfo lcmp;
    lcmp.name = "lcmp"; lcmp.args = 0;
    mapInstructions.insert({0x94, lcmp});

    instructionInfo lconst_0;
    lconst_0.name = "lconst_0"; lconst_0.args = 0;
    mapInstructions.insert({0x09, lconst_0});

    instructionInfo lconst_1;
    lconst_1.name = "lconst_1"; lconst_1.args = 0;
    mapInstructions.insert({0x0a, lconst_1});

    instructionInfo ldc;
    ldc.name = "ldc"; ldc.args = 1;
    mapInstructions.insert({0x12, ldc});

    instructionInfo ldc_w;
    ldc_w.name = "ldc_w"; ldc_w.args = 2;
    mapInstructions.insert({0x13, ldc_w});
    
    instructionInfo ldc2_w;
    ldc2_w.name = "ldc2_w"; ldc2_w.args = 2;
    mapInstructions.insert({0x14, ldc2_w});

    instructionInfo ldiv;
    ldiv.name = "ldiv"; ldiv.args = 0;
    mapInstructions.insert({0x6d, ldiv});

    instructionInfo lload;
    lload.name = "lload"; lload.args = 1;
    mapInstructions.insert({0x16, lload});

    instructionInfo lload_0;
    lload_0.name = "lload_0"; lload_0.args = 0;
    mapInstructions.insert({0x1e, lload_0});
    
    instructionInfo lload_1;
    lload_1.name = "lload_1"; lload_1.args = 0;
    mapInstructions.insert({0x1f, lload_1});

    instructionInfo lload_2;
    lload_2.name = "lload_2"; lload_2.args = 0;
    mapInstructions.insert({0x20, lload_2});

    instructionInfo lload_3;
    lload_3.name = "lload_3"; lload_3.args = 0;
    mapInstructions.insert({0x21, lload_3});

    instructionInfo lmul;
    lmul.name = "lmul"; lmul.args = 0;
    mapInstructions.insert({0x69, lmul});

    instructionInfo lneg;
    lneg.name = "lneg"; lneg.args = 0;
    mapInstructions.insert({0x75, lneg});

    instructionInfo lookupswitch;
    lookupswitch.name = "lookupswitch"; lookupswitch.args = 0;
    mapInstructions.insert({0xab, lookupswitch});

    instructionInfo lor;
    lor.name = "lor"; lor.args = 0;
    mapInstructions.insert({0x81, lor});

    instructionInfo lrem;
    lrem.name = "lrem"; lrem.args = 0;
    mapInstructions.insert({0x71, lrem});

    instructionInfo lreturn;
    lreturn.name = "lreturn"; lreturn.args = 0;
    mapInstructions.insert({0xad, lreturn});

    instructionInfo lshl;
    lshl.name = "lshl"; lshl.args = 0;
    mapInstructions.insert({0x79, lshl});

    instructionInfo lshr;
    lshr.name = "lshr"; lshr.args = 0;
    mapInstructions.insert({0x7b, lshr});

    instructionInfo lstore;
    lstore.name = "lstore"; lstore.args = 1;
    mapInstructions.insert({0x37, lstore});

    instructionInfo lstore_0;
    lstore_0.name = "lstore_0"; lstore_0.args = 0;
    mapInstructions.insert({0x3f, lstore_0});

    instructionInfo lstore_1;
    lstore_1.name = "lstore_1"; lstore_1.args = 0;
    mapInstructions.insert({0x40, lstore_1});

    instructionInfo lstore_2;
    lstore_2.name = "lstore_2"; lstore_2.args = 0;
    mapInstructions.insert({0x41, lstore_2});

    instructionInfo lstore_3;
    lstore_3.name = "lstore_3"; lstore_3.args = 0;
    mapInstructions.insert({0x42, lstore_3});

    instructionInfo lsub;
    lsub.name = "lsub"; lsub.args = 0;
    mapInstructions.insert({0x65, lsub});

    instructionInfo lushr;
    lushr.name = "lushr"; lushr.args = 0;
    mapInstructions.insert({0x7d, lushr});

    instructionInfo lxor;
    lxor.name = "lxor"; lxor.args = 0;
    mapInstructions.insert({0x83, lxor});

    instructionInfo monitorenter;
    monitorenter.name = "monitorenter"; monitorenter.args = 0;
    mapInstructions.insert({0xc2, monitorenter});

    instructionInfo monitorexit;
    monitorexit.name = "monitorexit"; monitorexit.args = 0;
    mapInstructions.insert({0xc3, monitorexit});

    instructionInfo multianewarray;
    multianewarray.name = "multianewarray"; multianewarray.args = 3;
    mapInstructions.insert({0xc5, multianewarray});

    instructionInfo jNew;
    jNew.name = "new\t"; jNew.args = 2;
    mapInstructions.insert({0xbb, jNew});

    instructionInfo newarray;
    newarray.name = "newarray"; newarray.args = 1;
    mapInstructions.insert({0xbc, newarray});

    instructionInfo nop;
    nop.name = "nop"; nop.args = 0;
    mapInstructions.insert({0x00, nop});

    instructionInfo pop;
    pop.name = "pop"; pop.args = 0;
    mapInstructions.insert({0x57, pop});

    instructionInfo pop2;
    pop2.name = "pop2"; pop2.args = 0;
    mapInstructions.insert({0x58, pop2});

    instructionInfo putfield;
    putfield.name = "putfield\t"; putfield.args = 2;
    mapInstructions.insert({0xb5, putfield});

    instructionInfo putstatic;
    putstatic.name = "putstatic"; putstatic.args = 2;
    mapInstructions.insert({0xb3, putstatic});
    
    instructionInfo ret;
    ret.name = "ret"; ret.args = 1;
    mapInstructions.insert({0xa9, ret});

    instructionInfo jReturn;
    jReturn.name = "return"; jReturn.args = 0;
    mapInstructions.insert({0xb1, jReturn});

    instructionInfo saload;
    saload.name = "saload"; saload.args = 0;
    mapInstructions.insert({0x35, saload});

    instructionInfo sastore;
    sastore.name = "sastore"; sastore.args = 0;
    mapInstructions.insert({0x56, sastore});

    instructionInfo sipush;
    sipush.name = "sipush"; sipush.args = 2;
    mapInstructions.insert({0x11, sipush});

    instructionInfo swap;
    swap.name = "swap"; swap.args = 0;
    mapInstructions.insert({0x5f, swap});

    instructionInfo tableswitch;
    tableswitch.name = "tableswitch"; tableswitch.args = 0;
    mapInstructions.insert({0xaa, tableswitch});

    instructionInfo wide;
    wide.name = "wide"; wide.args = 1;
    mapInstructions.insert({0xc4, wide});
}