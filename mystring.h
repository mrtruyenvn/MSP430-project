

//************************************************************************
unsigned int itemp;
int mystrlen(char *str)
{
	itemp = 0;
	while (str[itemp]!='\0')
	 {
		itemp++;
	 }
    return itemp;
 }
//************************************************************************
// Convert string to int
int mystrtoint(char *str)
{
	return (-1)*( 10*(str[0]-'0') + str[1]-'0' );
}
