//-----------------------------------------------------------------------------
// modules/JetCleaning.h
//-----------------------------------------------------------------------------

#ifndef JetCleaning_h
#define JetCleaning_h

#include "classes/DelphesModule.h"

class TObjArray;

class ExRootFilter;

class JetCleaning: public DelphesModule
{
public:

  JetCleaning();
  ~JetCleaning();

  void Init();
  void Process();
  void Finish();

private:

  Double_t fDeltaRMin;

  TIterator *fItCandidateInputArray; //!

  TIterator *fItJetInputArray; //!

  const TObjArray *fCandidateInputArray; //!

  const TObjArray *fJetInputArray; //!

  TObjArray *fOutputArray; //!

  ClassDef(JetCleaning, 1)
};

#endif
