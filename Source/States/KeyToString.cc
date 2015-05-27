#include "KeyToString.hpp"

std::string keyToString(sf::Keyboard::Key key){

	//# operator creates string literal
	#define RETURN_STRING(KEY) case sf::Keyboard::KEY: return #KEY;

	switch(key) {

		RETURN_STRING(Unknown)
		RETURN_STRING(A)
		RETURN_STRING(B)
		RETURN_STRING(C)
		RETURN_STRING(D)
		RETURN_STRING(E)
		RETURN_STRING(F)
		RETURN_STRING(G)
		RETURN_STRING(H)
		RETURN_STRING(I)
		RETURN_STRING(J)
		RETURN_STRING(K)
		RETURN_STRING(L)
		RETURN_STRING(M)
		RETURN_STRING(N)
		RETURN_STRING(O)
		RETURN_STRING(P)
		RETURN_STRING(Q)
		RETURN_STRING(R)
		RETURN_STRING(S)
		RETURN_STRING(T)
		RETURN_STRING(U)
		RETURN_STRING(V)
		RETURN_STRING(W)
		RETURN_STRING(X)
		RETURN_STRING(Y)
		RETURN_STRING(Z)
		RETURN_STRING(Num0)
		RETURN_STRING(Num1)
		RETURN_STRING(Num2)
		RETURN_STRING(Num3)
		RETURN_STRING(Num4)
		RETURN_STRING(Num5)
		RETURN_STRING(Num6)
		RETURN_STRING(Num7)
		RETURN_STRING(Num8)
		RETURN_STRING(Num9)
		RETURN_STRING(Escape)
		RETURN_STRING(LControl)
		RETURN_STRING(LShift)
		RETURN_STRING(LAlt)
		RETURN_STRING(LSystem)
		RETURN_STRING(RControl)
		RETURN_STRING(RShift)
		RETURN_STRING(RAlt)
		RETURN_STRING(RSystem)
		RETURN_STRING(Menu)
		RETURN_STRING(LBracket)
		RETURN_STRING(RBracket)
		RETURN_STRING(SemiColon)
		RETURN_STRING(Comma)
		RETURN_STRING(Period)
		RETURN_STRING(Quote)
		RETURN_STRING(Slash)
		RETURN_STRING(BackSlash)
		RETURN_STRING(Tilde)
		RETURN_STRING(Equal)
		RETURN_STRING(Dash)
		RETURN_STRING(Space)
		RETURN_STRING(Return)
		RETURN_STRING(BackSpace)
		RETURN_STRING(Tab)
		RETURN_STRING(PageUp)
		RETURN_STRING(PageDown)
		RETURN_STRING(End)
		RETURN_STRING(Home)
		RETURN_STRING(Insert)
		RETURN_STRING(Delete)
		RETURN_STRING(Add)
		RETURN_STRING(Subtract)
		RETURN_STRING(Multiply)
		RETURN_STRING(Divide)
		RETURN_STRING(Left)
		RETURN_STRING(Right)
		RETURN_STRING(Up)
		RETURN_STRING(Down)
		RETURN_STRING(Numpad0)
		RETURN_STRING(Numpad1)
		RETURN_STRING(Numpad2)
		RETURN_STRING(Numpad3)
		RETURN_STRING(Numpad4)
		RETURN_STRING(Numpad5)
		RETURN_STRING(Numpad6)
		RETURN_STRING(Numpad7)
		RETURN_STRING(Numpad8)
		RETURN_STRING(Numpad9)
		RETURN_STRING(F1)
		RETURN_STRING(F2)
		RETURN_STRING(F3)
		RETURN_STRING(F4)
		RETURN_STRING(F5)
		RETURN_STRING(F6)
		RETURN_STRING(F7)
		RETURN_STRING(F8)
		RETURN_STRING(F9)
		RETURN_STRING(F10)
		RETURN_STRING(F11)
		RETURN_STRING(F12)
		RETURN_STRING(F13)
		RETURN_STRING(F14)
		RETURN_STRING(F15)
		RETURN_STRING(Pause)
	}

	return "";
}


/* as per SFML 2.0 documentation

enum  	Key { 
  Unknown = -1, 
  A = 0, 
  B, 
  C, 
  D, 
  E, 
  F, 
  G, 
  H, 
  I, 
  J, 
  K, 
  L, 
  M, 
  N, 
  O, 
  P, 
  Q, 
  R, 
  S, 
  T, 
  U, 
  V, 
  W, 
  X, 
  Y, 
  Z, 
  Num0, 
  Num1, 
  Num2, 
  Num3, 
  Num4, 
  Num5, 
  Num6, 
  Num7, 
  Num8, 
  Num9, 
  Escape, 
  LControl, 
  LShift, 
  LAlt, 
  LSystem, 
  RControl, 
  RShift, 
  RAlt, 
  RSystem, 
  Menu, 
  LBracket, 
  RBracket, 
  SemiColon, 
  Comma, 
  Period, 
  Quote, 
  Slash, 
  BackSlash, 
  Tilde, 
  Equal, 
  Dash, 
  Space, 
  Return, 
  BackSpace, 
  Tab, 
  PageUp, 
  PageDown, 
  End, 
  Home, 
  Insert, 
  Delete, 
  Add, 
  Subtract, 
  Multiply, 
  Divide, 
  Left, 
  Right, 
  Up, 
  Down, 
  Numpad0, 
  Numpad1, 
  Numpad2, 
  Numpad3, 
  Numpad4, 
  Numpad5, 
  Numpad6, 
  Numpad7, 
  Numpad8, 
  Numpad9, 
  F1, 
  F2, 
  F3, 
  F4, 
  F5, 
  F6, 
  F7, 
  F8, 
  F9, 
  F10, 
  F11, 
  F12, 
  F13, 
  F14, 
  F15, 
  Pause, 
  KeyCount 
}*/