#ifndef GateBase_H
#define GateBase_H

class GateBase {
    public:
        virtual void setup() = 0;
        virtual void loop() = 0;
        virtual ~GateBase() {}
};

#endif