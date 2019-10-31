
// Lock manager implementing deterministic two-phase locking as described in
// 'The Case for Determinism in Database Systems'.

#include <deque>
#include "txn/lock_manager.h"

using std::deque;

deque<LockManager::LockRequest>* LockManager::getSpecificLockQueue(const Key* resourceKey){
  deque<LockRequest>* lockQueue = lock_table_[*resourceKey];
  if (lockQueue == nullptr){
    lockQueue = new deque<LockRequest>();
    lock_table_[*resourceKey] = lockQueue;
  }

  return lockQueue;
}

LockManagerA::LockManagerA(deque<Txn*>* ready_txns) {
  ready_txns_ = ready_txns;
}

bool LockManagerA::WriteLock(Txn* txn, const Key& key) {
  //
  // Implement this method!
  LockRequest newRequest(EXCLUSIVE, txn);
  deque<LockRequest>* lockQueue = getSpecificLockQueue(&key);

  bool isEmpty = lockQueue->empty();

  if (!isEmpty){
    txn_waits_[txn]++;
  }
  lockQueue->push_back(newRequest);

  return isEmpty;
}

bool LockManagerA::ReadLock(Txn* txn, const Key& key) {
  // Since Part 1A implements ONLY exclusive locks, calls to ReadLock can
  // simply use the same logic as 'WriteLock'.
  return WriteLock(txn, key);
}

void LockManagerA::Release(Txn* txn, const Key& key) {
  //
  // Implement this method!
  deque<LockRequest>* lockQueue = getSpecificLockQueue(&key);

  bool isLockOwner = true;
  for (auto itr = lockQueue->begin(); itr < lockQueue->end(); itr++){
    if (itr->txn_ == txn){
      lockQueue->erase(itr);
      break;
    }
    isLockOwner = false;
  }

  if (!lockQueue->empty() && isLockOwner){
    LockRequest nextRequest = lockQueue->front();
    txn_waits_[nextRequest.txn_]--;

    if (txn_waits_[nextRequest.txn_] == 0){
      ready_txns_->push_back(nextRequest.txn_);
      txn_waits_.erase(nextRequest.txn_);
    }
  }
}

LockMode LockManagerA::Status(const Key& key, vector<Txn*>* owners) {
  //
  // Implement this method!
  deque<LockRequest>* lockQueue = getSpecificLockQueue(&key);
  if (lockQueue->empty()){
    return UNLOCKED;
  }else {
    vector<Txn*> lockOwnerTransactions;
    lockOwnerTransactions.push_back(lockQueue->front().txn_);
    *owners = lockOwnerTransactions;
  }
  return EXCLUSIVE;
}

LockManagerB::LockManagerB(deque<Txn*>* ready_txns) {
  ready_txns_ = ready_txns;
}

bool LockManagerB::WriteLock(Txn* txn, const Key& key) {
  //
  // Implement this method!
  return true;
}

bool LockManagerB::ReadLock(Txn* txn, const Key& key) {
  //
  // Implement this method!
  return true;
}

void LockManagerB::Release(Txn* txn, const Key& key) {
  //
  // Implement this method!
}

LockMode LockManagerB::Status(const Key& key, vector<Txn*>* owners) {
  //
  // Implement this method!
  return UNLOCKED;
}

