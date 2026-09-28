// All tetris pieces with their rotations and displacement
#ifndef _PIECES_
#define _PIECES_

class Pieces
{
    public:
      int getBlocktype (int pPiece, int pRotation, int pX, int pY);
      int getXInitialPosition (int pPiece, int pRotation);
      int getYInitialPosition (int pPiece, int pRotation);
};

#endif