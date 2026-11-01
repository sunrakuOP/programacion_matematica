#pragma once

class ElementoFinito {
private:
    int numNodos;
public:
    ElementoFinito(int n);
    virtual ~ElementoFinito();

    int getNumNodos() const;
    virtual double area() = 0;
};
