#ifndef PHHEPMC_FUN4ALLHEPMCINPUTMANAGER_H
#define PHHEPMC_FUN4ALLHEPMCINPUTMANAGER_H

#include "PHHepMCGenHelper.h"

#include <fun4all/Fun4AllInputManager.h>
#include <fun4all/Fun4AllReturnCodes.h>

#include <boost/iostreams/filtering_streambuf.hpp>

#include <fstream>
#include <string>
#include <utility>  // for swap
#include <vector>

class PHCompositeNode;
class SyncObject;

// forward declaration of classes in namespace
namespace HepMC
{
  class IO_GenEvent;
  class GenEvent;
}  // namespace HepMC

class Fun4AllHepMCInputManager : public Fun4AllInputManager, public PHHepMCGenHelper
{
 public:
  Fun4AllHepMCInputManager(const std::string &name = "DUMMY", const std::string &nodename = "DST", const std::string &topnodename = "TOP");
  virtual ~Fun4AllHepMCInputManager();
  virtual int fileopen(const std::string &filenam);
  int fileclose();
  virtual int run(const int nevents = 0);
  virtual int ResetEvent();
  void ReadOscar(const int i) { m_ReadOscarFlag = i; }
  int ReadOscar() const { return m_ReadOscarFlag; }
  virtual void Print(const std::string &what = "ALL") const;
  virtual int PushBackEvents(const int i);

  // Effectivly turn off the synchronization checking
  //
  int SyncIt(const SyncObject * /*mastersync*/) { return Fun4AllReturnCodes::SYNC_OK; }
  int GetSyncObject(SyncObject ** /*mastersync*/) { return Fun4AllReturnCodes::SYNC_NOOBJECT; }
  int NoSyncPushBackEvents(const int nevt) { return PushBackEvents(nevt); }
  HepMC::GenEvent *ConvertFromOscar();

  virtual int SkipForThisManager(const int nevents) { return PushBackEvents(-nevents); }
  int MyCurrentEvent(const unsigned int index = 0) const;

 protected:
  HepMC::GenEvent *evt = nullptr;

  int events_total = 0;
  int events_thisfile = 0;
  int m_EventPushedBackFlag = 0;

  HepMC::IO_GenEvent *ascii_in = nullptr;

  std::string m_HepMCTmpFile;

 private:
  PHCompositeNode *topNode = nullptr;

  // some pointers for use in decompression handling
  std::ifstream *filestream = nullptr;  // holds compressed filestream
  std::istream *unzipstream = nullptr;  // feed into HepMc

  int m_ReadOscarFlag = 0;

  std::vector<int> m_MyEvent;

  boost::iostreams::filtering_streambuf<boost::iostreams::input> zinbuffer;

  std::ifstream theOscarFile;

  std::string filename;
  std::string topNodeName;
};

#endif /* PHHEPMC_FUN4ALLHEPMCINPUTMANAGER_H */
