#ifndef SvtxDeadMapv1_H__
#define SvtxDeadMapv1_H__

#include "SvtxDeadMap.h"

class SvtxDeadMapv1 : public SvtxDeadMap
{
 public:

  SvtxDeadMapv1()
  {
  }
  virtual ~SvtxDeadMapv1() {}
  virtual void Reset();
  virtual int isValid() const;

  virtual void identify(std::ostream &os = std::cout) const;
  virtual void addDeadChannel(const unsigned int layer, const unsigned int ieta, const unsigned int iphi);
  virtual void addDeadChannel(PHG4CellDefs::keytype key);

  virtual bool isDeadChannel(PHG4CellDefs::keytype key);
  virtual bool isDeadChannel(const unsigned int layer, const unsigned int ieta, const unsigned int iphi);
  //! return all towers
  virtual const Map &getDeadChannels(void) const;
  virtual Map &getDeadChannels(void);

  virtual unsigned int size() const { return m_DeadChannels.size(); }

 private:
  Map m_DeadChannels;

  ClassDef(SvtxDeadMapv1, 1)
};

#endif /* SvtxDeadMapv1_H__ */
