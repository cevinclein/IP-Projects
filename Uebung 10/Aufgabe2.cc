#include <iostream>
/* @VERBON */
class A
{
public:
  int ap;
  void X();
private:
  int aq;
  void aX();
};

class B : public A
{
public:
  int bp;
  void Y();
private:
  int bq;
  void bY();
};

class C : public B
{
public:
  int cp;
  void Z();
private:
  int cq;
  void cZ();
};

void A::X() { };
void A::aX() { };
void B::bY() { };
void C::Z() { };

void B::Y()
{
  bq = bp;
  aq = ap; //Auf private Variable aq in A kann nicht zugegriffen werden
  bY();
}

void C::cZ()
{
  ap = 1;
  bp = 2;
  cq = 3;
  X();
  Y();
  aX(); //aX() Ist schon privat in A kein zugriff möglich
}

int main()
{
  A a;  B b;  C c;

  a.X();
  b.bY(); //Von außen kein privater Zugriff auf by() möglich
  c.cp = 4;
  c.bp = 1;
  c.ap = 2;
  c.aq = 5; // aq schon in A privat 

  b.ap = c.ap;

  return 0;
}
/* @VERBOFF */
