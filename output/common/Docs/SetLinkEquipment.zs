void SetLinkEquipment(int a, int b){
	int equip;
	b = b << 8;
	equip &= b;
	equip &= a;
	Link->Equipment = equip;
}