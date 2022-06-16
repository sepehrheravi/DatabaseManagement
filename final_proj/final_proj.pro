TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        coperator.cpp \
        loperator.cpp \
        lparen.cpp \
        main.cpp \
        parser.cpp \
        recno.cpp \
        rparen.cpp \
        rpn.cpp \
        shuntingyard.cpp \
        sql.cpp \
        stoken.cpp \
        stokenizer.cpp \
        symbol.cpp \
        test_bplus_tree.cpp \
        token.cpp \
        tokenize.cpp

HEADERS += \
    !includes/add_entry.h \
    !includes/array_func.h \
    !includes/bplustree.h \
    !includes/linked_list_iterator.h \
    !includes/map.h \
    !includes/mmap.h \
    !includes/mpair.h \
    !includes/my_vector.h \
    !includes/node.h \
    !includes/oned.h \
    !includes/pair.h \
    !includes/queue.h \
    !includes/stack.h \
    constants.h \
    coperator.h \
    loperator.h \
    lparen.h \
    parser.h \
    recno.h \
    record.h \
    rparen.h \
    rpn.h \
    shuntingyard.h \
    sql.h \
    stoken.h \
    stokenizer.h \
    symbol.h \
    table.h \
    test_bplus_tree.h \
    token.h \
    tokenize.h \
    utility_funcs.h \
    z_final_proj_output.h \
    z_final_proj_work_report.h \
    z_test_bplustree_output.h
