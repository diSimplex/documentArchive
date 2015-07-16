#ifndef DISTRUCTURE_H
#define DISTRUCTURE_H

// NOTE this header is not meant to be included on its own...
// USE: #include <diSimplexEngine/disitt.h> instead

class DiStructureImpl;

class DiStructure {
public:

  bool isEmpty();

  bool contains(DiSimplex aSimplex);

  size_t sizeDim(size_t aDimension);

protected:

  DiStructure(DiStructureImpl *aDiStructure);

  DiStructureImpl *ref;

  friend class DiSITT;
  friend class DiSITTimpl;

};

class DiStructureImpl {



};

#endif
