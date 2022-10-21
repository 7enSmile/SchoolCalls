#include "../../include/viewmodel/callsmanager.h"



CallsManager::CallsManager(int type_, int special)
{

    m_listOfCalls = DbManager::getListCall(type_,special);
    count = m_listOfCalls->size();
    type = type_;

}

void CallsManager::insert(int h, int m, QString p, int s, int spt)
{
    Call* call = new Call(h,m,type,p,s,spt);
    DbManager::insert(call);
    call->id = DbManager::getId(call);
    m_listOfCalls->push_back(call);
    count++;
}

void CallsManager::remove(int index)
{
    DbManager::remove(m_listOfCalls->at(index)->id);
    m_listOfCalls->removeAt(index);
    count--;
}

void CallsManager::update(int index, int h, int m, QString p)
{
    m_listOfCalls->at(index)->hours = h;
    m_listOfCalls->at(index)->minutes = m;
    m_listOfCalls->at(index)->soundPatch = p;
    DbManager::update(m_listOfCalls->at(index));
}

void CallsManager::updateS(int index)
{
    m_listOfCalls->at(index)->saturday= !m_listOfCalls->at(index)->saturday;
    DbManager::update(m_listOfCalls->at(index));

}

void CallsManager::Find(int h, int m, int s, bool &flag, QString &p)
{
    Call call;
    DbManager::Find(h,m,s,flag,call);
    if (flag) {
        p = call.soundPatch;
    }
}

void CallsManager::get(int index, int &h, int &m, int &s)
{
    h =  m_listOfCalls->at(index)->hours;
    m = m_listOfCalls->at(index)->minutes;
    s = m_listOfCalls->at(index)->saturday;

}
