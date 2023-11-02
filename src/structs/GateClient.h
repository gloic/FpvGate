#pragma once

#include <Arduino.h>

struct GateClient : public Printable {
  int id;
  String ip;
  boolean isMock;

  GateClient(int id, String ip, boolean isMock): id(id), ip(ip), isMock(isMock) {}
  // GateClient(String ip, boolean isMock): ip(ip), isMock(isMock) {}
  size_t printTo(Print& p) const {
    size_t n = p.print("GateClient{ id=");
    n += p.print(id);
    n += p.print(", ip='");
    n += p.print(ip);
    n += p.print("', isMock=");
    n += p.print(isMock);
    n += p.print('}');
    return n;
}
};