
#include "ix.h"

IndexManager* IndexManager::_index_manager = 0;

IndexManager* IndexManager::instance()
{
    if(!_index_manager)
        _index_manager = new IndexManager();

    return _index_manager;
}

IndexManager::IndexManager()
{
}

IndexManager::~IndexManager()
{
}

RC IndexManager::createFile(const string &fileName)
{
    PagedFileManager *pfm = PagedFileManager::instance();

    if (pfm->createFile(fileName.c_str()) != 0)
    {
        return -1;
    }
    return 0;
}

RC IndexManager::destroyFile(const string &fileName)
{
    PagedFileManager *pfm = PagedFileManager::instance();
    if (pfm->destroyFile(fileName) != 0)
    {
        return -1;
    }
    return 0;
}

RC IndexManager::openFile(const string &fileName, IXFileHandle &ixfileHandle)
{
    PagedFileManager *pfm = PagedFileManager::instance();
    if (pfm->openFile(fileName, ixfileHandle.fh) != 0)
    {
        return -1;
    }
    return 0;
}

RC IndexManager::closeFile(IXFileHandle &ixfileHandle)
{
    PagedFileManager *pfm = PagedFileManager::instance();
    if (pfm->closeFile(ixfileHandle.fh) != 0)
    {
        return -1;
    }
    return 0;
}

RC IndexManager::insertEntry(IXFileHandle &ixfileHandle, const Attribute &attribute, const void *key, const RID &rid)
{
    return -1;
}

RC IndexManager::deleteEntry(IXFileHandle &ixfileHandle, const Attribute &attribute, const void *key, const RID &rid)
{
    return -1;
}


RC IndexManager::scan(IXFileHandle &ixfileHandle,
                      const Attribute &attribute,
                      const void      *lowKey,
                      const void      *highKey,
                      boollowKeyInclusive,
                      bool        highKeyInclusive,
                      IX_ScanIterator &ix_ScanIterator)
{
    return -1;
}

void IndexManager::printBtree(IXFileHandle &ixfileHandle, const Attribute &attribute) const {
}

IX_ScanIterator::IX_ScanIterator()
{
}

IX_ScanIterator::~IX_ScanIterator()
{
}

RC IX_ScanIterator::getNextEntry(RID &rid, void *key)
{
    return -1;
}

RC IX_ScanIterator::close()
{
    return -1;
}


IXFileHandle::IXFileHandle()
{
    ixReadPageCounter = 0;
    ixWritePageCounter = 0;
    ixAppendPageCounter = 0;
}

IXFileHandle::~IXFileHandle()
{
}

RC IXFileHandle::collectCounterValues(unsigned &readPageCount, unsigned &writePageCount, unsigned &appendPageCount)
{
    return -1;
}
