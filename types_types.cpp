/**
 * Autogenerated by Thrift Compiler (0.9.2)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "types_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>




THostPort::~THostPort() throw() {
}


void THostPort::__set_ip(const std::string& val) {
  this->ip = val;
}

void THostPort::__set_port(const int32_t val) {
  this->port = val;
}

const char* THostPort::ascii_fingerprint = "EEBC915CE44901401D881E6091423036";
const uint8_t THostPort::binary_fingerprint[16] = {0xEE,0xBC,0x91,0x5C,0xE4,0x49,0x01,0x40,0x1D,0x88,0x1E,0x60,0x91,0x42,0x30,0x36};

uint32_t THostPort::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->ip);
          this->__isset.ip = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->port);
          this->__isset.port = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t THostPort::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  oprot->incrementRecursionDepth();
  xfer += oprot->writeStructBegin("THostPort");

  xfer += oprot->writeFieldBegin("ip", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->ip);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("port", ::apache::thrift::protocol::T_I32, 2);
  xfer += oprot->writeI32(this->port);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  oprot->decrementRecursionDepth();
  return xfer;
}

void swap(THostPort &a, THostPort &b) {
  using ::std::swap;
  swap(a.ip, b.ip);
  swap(a.port, b.port);
  swap(a.__isset, b.__isset);
}

THostPort::THostPort(const THostPort& other0) {
  ip = other0.ip;
  port = other0.port;
  __isset = other0.__isset;
}
THostPort& THostPort::operator=(const THostPort& other1) {
  ip = other1.ip;
  port = other1.port;
  __isset = other1.__isset;
  return *this;
}
std::ostream& operator<<(std::ostream& out, const THostPort& obj) {
  using apache::thrift::to_string;
  out << "THostPort(";
  out << "ip=" << to_string(obj.ip);
  out << ", " << "port=" << to_string(obj.port);
  out << ")";
  return out;
}


QuerySpec::~QuerySpec() throw() {
}


void QuerySpec::__set_name(const std::string& val) {
  this->name = val;
__isset.name = true;
}

void QuerySpec::__set_input(const std::string& val) {
  this->input = val;
}

void QuerySpec::__set_timestamp(const std::vector<int64_t> & val) {
  this->timestamp = val;
}

void QuerySpec::__set_budget(const double val) {
  this->budget = val;
}

const char* QuerySpec::ascii_fingerprint = "7F2C64C93BB20002149DCE29E7E29674";
const uint8_t QuerySpec::binary_fingerprint[16] = {0x7F,0x2C,0x64,0xC9,0x3B,0xB2,0x00,0x02,0x14,0x9D,0xCE,0x29,0xE7,0xE2,0x96,0x74};

uint32_t QuerySpec::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->name);
          this->__isset.name = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->input);
          this->__isset.input = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->timestamp.clear();
            uint32_t _size2;
            ::apache::thrift::protocol::TType _etype5;
            xfer += iprot->readListBegin(_etype5, _size2);
            this->timestamp.resize(_size2);
            uint32_t _i6;
            for (_i6 = 0; _i6 < _size2; ++_i6)
            {
              xfer += iprot->readI64(this->timestamp[_i6]);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.timestamp = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_DOUBLE) {
          xfer += iprot->readDouble(this->budget);
          this->__isset.budget = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t QuerySpec::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  oprot->incrementRecursionDepth();
  xfer += oprot->writeStructBegin("QuerySpec");

  if (this->__isset.name) {
    xfer += oprot->writeFieldBegin("name", ::apache::thrift::protocol::T_STRING, 1);
    xfer += oprot->writeString(this->name);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldBegin("input", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeBinary(this->input);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("timestamp", ::apache::thrift::protocol::T_LIST, 3);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_I64, static_cast<uint32_t>(this->timestamp.size()));
    std::vector<int64_t> ::const_iterator _iter7;
    for (_iter7 = this->timestamp.begin(); _iter7 != this->timestamp.end(); ++_iter7)
    {
      xfer += oprot->writeI64((*_iter7));
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("budget", ::apache::thrift::protocol::T_DOUBLE, 4);
  xfer += oprot->writeDouble(this->budget);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  oprot->decrementRecursionDepth();
  return xfer;
}

void swap(QuerySpec &a, QuerySpec &b) {
  using ::std::swap;
  swap(a.name, b.name);
  swap(a.input, b.input);
  swap(a.timestamp, b.timestamp);
  swap(a.budget, b.budget);
  swap(a.__isset, b.__isset);
}

QuerySpec::QuerySpec(const QuerySpec& other8) {
  name = other8.name;
  input = other8.input;
  timestamp = other8.timestamp;
  budget = other8.budget;
  __isset = other8.__isset;
}
QuerySpec& QuerySpec::operator=(const QuerySpec& other9) {
  name = other9.name;
  input = other9.input;
  timestamp = other9.timestamp;
  budget = other9.budget;
  __isset = other9.__isset;
  return *this;
}
std::ostream& operator<<(std::ostream& out, const QuerySpec& obj) {
  using apache::thrift::to_string;
  out << "QuerySpec(";
  out << "name="; (obj.__isset.name ? (out << to_string(obj.name)) : (out << "<null>"));
  out << ", " << "input=" << to_string(obj.input);
  out << ", " << "timestamp=" << to_string(obj.timestamp);
  out << ", " << "budget=" << to_string(obj.budget);
  out << ")";
  return out;
}


RegMessage::~RegMessage() throw() {
}


void RegMessage::__set_app_name(const std::string& val) {
  this->app_name = val;
}

void RegMessage::__set_endpoint(const THostPort& val) {
  this->endpoint = val;
}

void RegMessage::__set_budget(const double val) {
  this->budget = val;
}

const char* RegMessage::ascii_fingerprint = "B61C91CEFA669A76958C50E9981CDEEA";
const uint8_t RegMessage::binary_fingerprint[16] = {0xB6,0x1C,0x91,0xCE,0xFA,0x66,0x9A,0x76,0x95,0x8C,0x50,0xE9,0x98,0x1C,0xDE,0xEA};

uint32_t RegMessage::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->app_name);
          this->__isset.app_name = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->endpoint.read(iprot);
          this->__isset.endpoint = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_DOUBLE) {
          xfer += iprot->readDouble(this->budget);
          this->__isset.budget = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t RegMessage::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  oprot->incrementRecursionDepth();
  xfer += oprot->writeStructBegin("RegMessage");

  xfer += oprot->writeFieldBegin("app_name", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->app_name);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("endpoint", ::apache::thrift::protocol::T_STRUCT, 2);
  xfer += this->endpoint.write(oprot);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("budget", ::apache::thrift::protocol::T_DOUBLE, 3);
  xfer += oprot->writeDouble(this->budget);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  oprot->decrementRecursionDepth();
  return xfer;
}

void swap(RegMessage &a, RegMessage &b) {
  using ::std::swap;
  swap(a.app_name, b.app_name);
  swap(a.endpoint, b.endpoint);
  swap(a.budget, b.budget);
  swap(a.__isset, b.__isset);
}

RegMessage::RegMessage(const RegMessage& other10) {
  app_name = other10.app_name;
  endpoint = other10.endpoint;
  budget = other10.budget;
  __isset = other10.__isset;
}
RegMessage& RegMessage::operator=(const RegMessage& other11) {
  app_name = other11.app_name;
  endpoint = other11.endpoint;
  budget = other11.budget;
  __isset = other11.__isset;
  return *this;
}
std::ostream& operator<<(std::ostream& out, const RegMessage& obj) {
  using apache::thrift::to_string;
  out << "RegMessage(";
  out << "app_name=" << to_string(obj.app_name);
  out << ", " << "endpoint=" << to_string(obj.endpoint);
  out << ", " << "budget=" << to_string(obj.budget);
  out << ")";
  return out;
}


RegReply::~RegReply() throw() {
}


void RegReply::__set_service_list(const std::vector<THostPort> & val) {
  this->service_list = val;
}

void RegReply::__set_final_stage(const bool val) {
  this->final_stage = val;
}

const char* RegReply::ascii_fingerprint = "07B7E0B5CBB16B38AD46D3C055CB12C2";
const uint8_t RegReply::binary_fingerprint[16] = {0x07,0xB7,0xE0,0xB5,0xCB,0xB1,0x6B,0x38,0xAD,0x46,0xD3,0xC0,0x55,0xCB,0x12,0xC2};

uint32_t RegReply::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->service_list.clear();
            uint32_t _size12;
            ::apache::thrift::protocol::TType _etype15;
            xfer += iprot->readListBegin(_etype15, _size12);
            this->service_list.resize(_size12);
            uint32_t _i16;
            for (_i16 = 0; _i16 < _size12; ++_i16)
            {
              xfer += this->service_list[_i16].read(iprot);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.service_list = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_BOOL) {
          xfer += iprot->readBool(this->final_stage);
          this->__isset.final_stage = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t RegReply::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  oprot->incrementRecursionDepth();
  xfer += oprot->writeStructBegin("RegReply");

  xfer += oprot->writeFieldBegin("service_list", ::apache::thrift::protocol::T_LIST, 1);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->service_list.size()));
    std::vector<THostPort> ::const_iterator _iter17;
    for (_iter17 = this->service_list.begin(); _iter17 != this->service_list.end(); ++_iter17)
    {
      xfer += (*_iter17).write(oprot);
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("final_stage", ::apache::thrift::protocol::T_BOOL, 2);
  xfer += oprot->writeBool(this->final_stage);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  oprot->decrementRecursionDepth();
  return xfer;
}

void swap(RegReply &a, RegReply &b) {
  using ::std::swap;
  swap(a.service_list, b.service_list);
  swap(a.final_stage, b.final_stage);
  swap(a.__isset, b.__isset);
}

RegReply::RegReply(const RegReply& other18) {
  service_list = other18.service_list;
  final_stage = other18.final_stage;
  __isset = other18.__isset;
}
RegReply& RegReply::operator=(const RegReply& other19) {
  service_list = other19.service_list;
  final_stage = other19.final_stage;
  __isset = other19.__isset;
  return *this;
}
std::ostream& operator<<(std::ostream& out, const RegReply& obj) {
  using apache::thrift::to_string;
  out << "RegReply(";
  out << "service_list=" << to_string(obj.service_list);
  out << ", " << "final_stage=" << to_string(obj.final_stage);
  out << ")";
  return out;
}


