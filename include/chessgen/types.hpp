#pragma once

#include "platform.hpp"

namespace chessgen
{
enum class Direction {
  North,
  South,
  East,
  West,
  NorthEast,
  NorthWest,
  SouthEast,
  SouthWest,
  Count,
};

enum class File {
  FileA,
  FileB,
  FileC,
  FileD,
  FileE,
  FileF,
  FileG,
  FileH,

  Count,
  None = Count,
};

enum class Rank {
  Rank1,
  Rank2,
  Rank3,
  Rank4,
  Rank5,
  Rank6,
  Rank7,
  Rank8,

  Count,
  None = Count,
};

inline File operator++(File& f)
{
  CG_ASSERT(f <= File::FileH);
  return f = File(static_cast<int>(f) + 1);
}
inline File operator--(File& f)
{
  CG_ASSERT(f >= File::FileA);
  return f = File(static_cast<int>(f) - 1);
}

inline Rank operator++(Rank& r)
{
  CG_ASSERT(r <= Rank::Rank8);
  return r = Rank(static_cast<int>(r) + 1);
}
inline Rank operator--(Rank& r)
{
  CG_ASSERT(r >= Rank::Rank1);
  return r = Rank(static_cast<int>(r) - 1);
}

enum class Square {
  // clang-format off
  A1, B1, C1, D1, E1, F1, G1, H1,
  A2, B2, C2, D2, E2, F2, G2, H2,
  A3, B3, C3, D3, E3, F3, G3, H3,
  A4, B4, C4, D4, E4, F4, G4, H4,
  A5, B5, C5, D5, E5, F5, G5, H5,
  A6, B6, C6, D6, E6, F6, G6, H6,
  A7, B7, C7, D7, E7, F7, G7, H7,
  A8, B8, C8, D8, E8, F8, G8, H8,
  Count,
  // clang-format on
};
constexpr inline Square squareFromIndex(int index) { return Square(index); }
constexpr inline int    indexFromSquare(Square square) { return int(square); }
constexpr inline Square makeSquare(File f, Rank r)
{
  CG_ASSERT(f >= File::FileA && f <= File::FileH);
  CG_ASSERT(r >= Rank::Rank1 && r <= Rank::Rank8);
  return Square((static_cast<int>(r) << 3) + static_cast<int>(f));
}
constexpr inline File getFile(Square s)
{
  CG_ASSERT(s >= Square::A1 && s <= Square::H8);
  return File(static_cast<int>(s) & 7);
}
constexpr inline Rank getRank(Square s)
{
  CG_ASSERT(s >= Square::A1 && s <= Square::H8);
  return Rank(static_cast<int>(s) >> 3);
}

inline Square operator++(Square& s)
{
  CG_ASSERT(s <= Square::H8);
  return s = Square(static_cast<int>(s) + 1);
}
inline Square operator--(Square& s)
{
  CG_ASSERT(s >= Square::A1);
  return s = Square(static_cast<int>(s) - 1);
}

// Pieces are often used as an index into a piece array
// I don't like using C enums, but C++ scoped enums
// cannot be implicitly converted to integers, which would
// require casts for every access into the arrays
// This is my middle ground solution.
struct PieceEnum {
  enum Piece_ {
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King,
    Count,
    None = Count,
  };
};
using Piece = PieceEnum::Piece_;

enum Color {
  White,
  Black,
};

inline std::string to_string(Rank r)
{
  return std::string{static_cast<char>(static_cast<int>(r) + '0')};
}
inline std::string to_string(File f)
{
  return std::string{static_cast<char>(static_cast<int>(f) + 'a')};
}
inline std::string to_string(Square s) { return to_string(getFile(s)) + to_string(getRank(s)); }
inline std::string to_string(Piece p)
{
  switch (p) {
    case Piece::Pawn:
      return "P";
    case Piece::Rook:
      return "R";
    case Piece::Bishop:
      return "B";
    case Piece::Knight:
      return "N";
    case Piece::King:
      return "K";
    case Piece::Queen:
      return "Q";
    case Piece::Count:
    default:
      throw std::runtime_error("Invalid piece");
  }
}
}  // namespace chessgen
