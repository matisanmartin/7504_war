void ValidarLimites(int NumFilas, int NumCol, int PosX, int PosY, int InfX, int InfY, int & LimIzq, 
					int & LimDer, int & LimSup, int & LimInf)
{
		if((LimIzq=PosX-InfX)<0)
			LimIzq=0;
		
		if((LimSup=PosY-InfY)<0)
			LimSup=0;
	
		if((LimDer=PosX+InfX)>=NumCol)
			LimDer=NumFilas-1;
		
		if((LimInf=PosY+InfY)>=NumFilas)
			LimInf=NumCol-1;
}


