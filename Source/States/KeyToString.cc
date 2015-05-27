#include "KeyToString.hpp"

std::string keyToString(sf::Keyboard::Key key){

	//# operator creates string literal
	#define RETURN_STRING(KEY) case sf::Keyboard::KEY: return #KEY;

	switch(key) {

		RETURN_STRING(Unknown)
		RETURN_STRING(A) //0
		RETURN_STRING(B) //1
		RETURN_STRING(C) //2
		RETURN_STRING(D) //3
		RETURN_STRING(E) //4
		RETURN_STRING(F) //5
		RETURN_STRING(G) //6
		RETURN_STRING(H) //7
		RETURN_STRING(I) //8
		RETURN_STRING(J) //9
		RETURN_STRING(K) //10
		RETURN_STRING(L) //11
		RETURN_STRING(M) //12
		RETURN_STRING(N) //13
		RETURN_STRING(O) //14
		RETURN_STRING(P) //15
		RETURN_STRING(Q) //16
		RETURN_STRING(R) //17
		RETURN_STRING(S) //18
		RETURN_STRING(T) //19
		RETURN_STRING(U) //20
		RETURN_STRING(V) //21
		RETURN_STRING(W) //22
		RETURN_STRING(X) //23
		RETURN_STRING(Y) //24
		RETURN_STRING(Z) //25
		RETURN_STRING(Num0) //26
		RETURN_STRING(Num1) //27
		RETURN_STRING(Num2) //28
		RETURN_STRING(Num3) //29
		RETURN_STRING(Num4) //30
		RETURN_STRING(Num5) //31
		RETURN_STRING(Num6) //32
		RETURN_STRING(Num7) //33
		RETURN_STRING(Num8) //34
		RETURN_STRING(Num9) //35
		RETURN_STRING(Escape) //36
		RETURN_STRING(LControl) //37
		RETURN_STRING(LShift) //38
		RETURN_STRING(LAlt) //39
		RETURN_STRING(LSystem) //40
		RETURN_STRING(RControl) //41
		RETURN_STRING(RShift) //42
		RETURN_STRING(RAlt) //43
		RETURN_STRING(RSystem) //44
		RETURN_STRING(Menu) //45
		RETURN_STRING(LBracket) //46
		RETURN_STRING(RBracket) //47
		RETURN_STRING(SemiColon) //48
		RETURN_STRING(Comma) //49
		RETURN_STRING(Period) //50
		RETURN_STRING(Quote) //51
		RETURN_STRING(Slash) //52
		RETURN_STRING(BackSlash) //53
		RETURN_STRING(Tilde) //54
		RETURN_STRING(Equal) //55
		RETURN_STRING(Dash) //56
		RETURN_STRING(Space) //57
		RETURN_STRING(Return) //58
		RETURN_STRING(BackSpace) //59
		RETURN_STRING(Tab) //60
		RETURN_STRING(PageUp) //61
		RETURN_STRING(PageDown) //62
		RETURN_STRING(End) //63
		RETURN_STRING(Home) //64
		RETURN_STRING(Insert) //65
		RETURN_STRING(Delete) //66
		RETURN_STRING(Add) //67
		RETURN_STRING(Subtract) //68
		RETURN_STRING(Multiply) //69
		RETURN_STRING(Divide) //70
		RETURN_STRING(Left) //71
		RETURN_STRING(Right) //72
		RETURN_STRING(Up) //73
		RETURN_STRING(Down) //74
		RETURN_STRING(Numpad0) //75
		RETURN_STRING(Numpad1) //76
		RETURN_STRING(Numpad2) //77
		RETURN_STRING(Numpad3) //78
		RETURN_STRING(Numpad4) //79
		RETURN_STRING(Numpad5) //80
		RETURN_STRING(Numpad6) //81
		RETURN_STRING(Numpad7) //82
		RETURN_STRING(Numpad8) //83
		RETURN_STRING(Numpad9) //84
		RETURN_STRING(F1) //85
		RETURN_STRING(F2) //86
		RETURN_STRING(F3) //87
		RETURN_STRING(F4) //88
		RETURN_STRING(F5) //89
		RETURN_STRING(F6) //90
		RETURN_STRING(F7) //91
		RETURN_STRING(F8) //92
		RETURN_STRING(F9) //93
		RETURN_STRING(F10) //94
		RETURN_STRING(F11) //95
		RETURN_STRING(F12) //96
		RETURN_STRING(F13) //97
		RETURN_STRING(F14) //98
		RETURN_STRING(F15) //99
		RETURN_STRING(Pause) //100
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