#include "CDBUtils.h"

#include "SphenixClient.h"

#include <nlohmann/json.hpp>

#include <iostream>
#include <stdexcept>

CDBUtils::CDBUtils()
  : cdbclient(new SphenixClient())
{
}

CDBUtils::CDBUtils(const std::string &globaltag)
  : cdbclient(new SphenixClient(globaltag))
{
}

int CDBUtils::createGlobalTag(const std::string &tagname)
{
  nlohmann::json resp = cdbclient->createGlobalTag(tagname);
  int iret = resp["code"];
  nlohmann::json msgcont = resp["msg"];
  std::cout << msgcont << std::endl;
  return iret;
}

int CDBUtils::deleteGlobalTag(const std::string &tagname)
{
  nlohmann::json resp = cdbclient->deleteGlobalTag(tagname);
  int iret = resp["code"];
  nlohmann::json msgcont = resp["msg"];
  std::cout << msgcont << std::endl;
  return iret;
}

int CDBUtils::lockGlobalTag(const std::string &tagname)
{
  nlohmann::json resp = cdbclient->lockGlobalTag(tagname);
  int iret = resp["code"];
  nlohmann::json msgcont = resp["msg"];
  std::cout << msgcont << std::endl;
  return iret;
}

int CDBUtils::unlockGlobalTag(const std::string &tagname)
{
  nlohmann::json resp = cdbclient->unlockGlobalTag(tagname);
  int iret = resp["code"];
  nlohmann::json msgcont = resp["msg"];
  std::cout << "message: " << msgcont << std::endl;
  return iret;
}

void CDBUtils::clearCache()
{
  cdbclient->clearCache();
}

std::string CDBUtils::getUrl(const std::string &type, uint64_t iov)
{
  nlohmann::json resp = cdbclient->getUrl(type, iov);
  return resp["msg"];
}

int CDBUtils::createPayloadType(const std::string &pt)
{
  return cdbclient->createDomain(pt);
}

void CDBUtils::listPayloadIOVs(uint64_t iov)
{
  nlohmann::json resp = cdbclient->getPayloadIOVs(iov);
  if (resp["code"] != 0)
  {
    std::cout <<  resp["msg"] << std::endl;
    return;
  }
  nlohmann::json payload_iovs = resp["msg"];
  for (auto & [pt, val] : payload_iovs.items())
  {
    std::cout <<  pt << ": " << val["payload_url"]
	      << ", begin ts: " << val["minor_iov_start"]
	      << ", end ts: " << val["minor_iov_end"]
              << std::endl;
  }
  return;
}

int CDBUtils::cloneGlobalTag(const std::string& source, const std::string& target)
{
  nlohmann::json resp = cdbclient->getGlobalTags();
  nlohmann::json msgcont = resp["msg"];
  std::set<std::string> gtset;
  for (auto &it : msgcont.items())
  {
    std::string exist_gt = it.value().at("name");
    gtset.insert(exist_gt);
  }
  if (gtset.find(source) == gtset.end())
  {
    std::cout << "source tag " << source << " does not exist" << std::endl;
    return -1;
  }
  if (gtset.find(target) != gtset.end())
  {
    std::cout << "Target tag " << target << " exists, delete it first" << std::endl;
    return -1;
  }
  resp = cdbclient->cloneGlobalTag(source, target);
  int iret = resp["code"];
  std::cout << resp["msg"] << std::endl;
  return iret;
}

void CDBUtils::listGlobalTags()
{
  nlohmann::json resp = cdbclient->getGlobalTags();
  nlohmann::json msgcont = resp["msg"];
  for (auto &it : msgcont.items())
  {
    std::string exist_gt = it.value().at("name");
    std::cout << "global tag: " << exist_gt << std::endl;
  }
  return;
}

void CDBUtils::listPayloadTypes()
{
  nlohmann::json resp = cdbclient->getPayloadTypes();
  nlohmann::json msgcont = resp["msg"];
  for (auto &it : msgcont.items())
  {
    std::string exist_pl = it.value().at("name");
    std::cout << "payload type: " << exist_pl << std::endl;
  }
  return;
}

int CDBUtils::insertPayload(const std::string &pl_type, const std::string &file_url, uint64_t iov_start)
{
  if (!isGlobalTagSet())
  {
    std::cout << "No Global Tag set" << std::endl;
    return -1;
  }
  nlohmann::json resp = cdbclient->insertPayload(pl_type, file_url, iov_start);
  int iret = resp["code"];
  if (iret != 0)
  {
    std::cout << "Error inserting payload " << file_url << ", msg: " << resp["msg"] << std::endl;
  }
  else
  {
    std::cout << resp["msg"] << std::endl;
  }
  return iret;
}

int CDBUtils::insertPayload(const std::string &pl_type, const std::string &file_url, uint64_t iov_start, uint64_t iov_end)
{
  if (!isGlobalTagSet())
  {
    std::cout << "No Global Tag set" << std::endl;
    return -1;
  }
  nlohmann::json resp = cdbclient->insertPayload(pl_type, file_url, iov_start, iov_end);
  int iret = resp["code"];
  if (iret != 0)
  {
    std::cout << "Error inserting payload " << file_url << ", msg: " << resp["msg"] << std::endl;
  }
  else
  {
    std::cout << resp["msg"] << std::endl;
  }
  return iret;
}

int CDBUtils::setGlobalTag(const std::string &tagname)
{
  nlohmann::json resp = cdbclient->setGlobalTag(tagname);
  int iret = resp["code"];
  std::cout << "message: " << resp["msg"] << std::endl;
  return iret;
}

bool CDBUtils::isGlobalTagSet()
{
  return cdbclient->isGlobalTagSet();
}

void CDBUtils::Verbosity(int i)
{
  if (cdbclient)
  {
    cdbclient->Verbosity(i);
  }
  m_Verbosity = i;
}