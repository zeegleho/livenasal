
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
template< class T = simSymbol >
class simSymbolTableVisitor{
virtual void start( int num_symbols);
virtual void action(T *sym);
virtual void finish();
}

template< class T = simSymbol >
class simSymbolTable{
    getSize();
    find();
    insert();
    get();
    replace();
    remove();

    doVisit();


    class context_iterator{
    }

    map<T> _symbols;
    T **_ord_symbols;
    int _size;
}
