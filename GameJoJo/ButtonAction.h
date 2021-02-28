#ifndef GAME_JOJO_BUTTON_ACTION_H
#define GAME_JOJO_BUTTON_ACTION_H

class CButtonAction {
public:
  // default constructor
  CButtonAction();
  CListNode ba_lnNode;
  INDEX ba_iFirstKey;
  BOOL ba_bFirstKeyDown;
  INDEX ba_iSecondKey;
  BOOL ba_bSecondKeyDown;
  CTString ba_strName;
  CTString ba_strCommandLineWhenPressed;
  CTString ba_strCommandLineWhenReleased;
  // Assignment operator.
  virtual CButtonAction &operator=(CButtonAction &baOriginal);
  virtual void Read_t( CTStream &istrm);    // throw char*
  virtual void Write_t( CTStream &ostrm);    // throw char*
};

#endif
