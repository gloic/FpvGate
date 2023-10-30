#pragma once

#include <Arduino.h>

struct GateClient {
  int id;
  String ip;
  boolean isMock;

  GateClient(int _id, String _ip, boolean _isMock) : id(_id), ip(_ip), isMock(_isMock) {}
};