#ifndef QTABLE_H_
#define QTABLE_H_

#include "qdecision.h"


namespace ns3 {

class QTableEntry : public QDecisionEntry {
public:
  QTableEntry();
  QTableEntry(Ipv4Address, Time, float c_threshold, float lm_threshold, Ipv4Address myip);
  ~QTableEntry();

  void SetQValue(Time t, bool verbose = false);
  void SetSenderConverged(bool b);
  void Unconverge();
  bool LearnMore();
  bool LearnLess();
  void AddStrike();
  void DeductStrike();
};

class QTable : public QDecision {
public:
  QTable();
  QTable(std::vector<Ipv4Address>, Ipv4Address, float, float, float, std::vector<Ipv4Address>, std::string, bool, bool, float);
  ~QTable();

  // true if destination is already in our list of destinations
  bool CheckDestinationKnown(const Ipv4Address& i);

  bool AddDestination(Ipv4Address via, Ipv4Address dst, Time t);

  void Update(Ipv4Address, Ipv4Address, Time, Time, Time);
  //used exclusively in QoS QLearner to converge more easily ...
  uint64_t CalculateNewQValue(Ipv4Address, Ipv4Address, Time, Time, Time);

  QDecisionEntry* GetNextEstim(Ipv4Address);
  QDecisionEntry* GetNextEstim(Ipv4Address,Ipv4Address);
  QDecisionEntry* GetNextEstim(Ipv4Address,Ipv4Address,Ipv4Address);
  QDecisionEntry* GetNextEstimToLearn(Ipv4Address);
  QDecisionEntry* GetRandomEstim(Ipv4Address,bool=false);
  QDecisionEntry* GetEntryByRef(Ipv4Address,Ipv4Address);

  bool AllNeighboursBlacklisted(Ipv4Address);
  std::string PrettyPrint(std::string="");
//  void PrettyPrintToCout() { std::cout << PrettyPrint(); }
  void ToFile(std::string filename);
  void FinalFile();
  void ChangeQValuesFromZero(Ipv4Address dst, Ipv4Address aodv_next_hop) ;
  void MarkNeighbDown(Ipv4Address);
  void AddNeighbour(Ipv4Address);

  bool IsNeighbourAvailable(Ipv4Address);

  bool HasConverged(Ipv4Address dst, bool = false);

  void Unconverge();

  bool LearnLess(Ipv4Address);
  bool LearnMore(Ipv4Address);

  void SetQValueWrapper(Ipv4Address,Ipv4Address,Time);

//  std::vector<QDecisionEntry*> GetEstims(Ipv4Address dst) {
//	return m_qtable[dst];
//  }

private:
  void RemoveNeighbour(Ipv4Address);
  	std::map<Ipv4Address, std::vector<QDecisionEntry*> > m_qtable;
};

} //namespace ns3

#endif /* QTABLE_H */
