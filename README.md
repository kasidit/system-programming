# system-programming

## ศึกษา Duff's Device
<p>
ให้ นศ ศึกษา duff device ที่ <a href="http://www.lysator.liu.se/c/duffs-device.html">reference [1]</a> ข้างล่าง แล้วพิจารณาว่าทำไม  Tom Duff จึงเปลี่ยน โค๊ด จาก 
<pre>
	send(to, from, count)
	register short *to, *from;
	register count;
	{
		do
			*to = *from++;
		while(--count>0);
	}
</pre>
ให้เป็น 
<pre>
	send(to, from, count)
	register short *to, *from;
	register count;
	{
		register n=(count+7)/8;
		switch(count%8){
		case 0:	do{	*to = *from++;
		case 7:		*to = *from++;
		case 6:		*to = *from++;
		case 5:		*to = *from++;
		case 4:		*to = *from++;
		case 3:		*to = *from++;
		case 2:		*to = *from++;
		case 1:		*to = *from++;
			}while(--n>0);
		}
	}
</pre>
ได้ ในโปรแกรมนี้ขึ้นขึ้นเพื่อ copy ค่าจาก array ของ short ไปยังรีจิสเตอร์ของ Programmed IO data register ของเครื่องคอมพิวเตอร์ Evans & Sutherland Picture System II 
<p>
ใน code <a href="https://github.com/kasidit/system-programming/blob/master/src/duff/duff.c">src/duff/duff.c</a> ผมได้แปลงให้เป็นการก็อปปี้ค่า array ของ characters จาก array *from ไปยัง *to คือให้เปลี่ยนจาก 
<pre>
	do
		*to++ = *from++;
	while(--count>0);
</pre>
เป็น 
<pre>
	register int n=(count+7)/8;
	switch(count%8){
	case 0:	do{	*to++ = *from++;
	case 7:		*to++ = *from++;
	case 6:		*to++ = *from++;
	case 5:		*to++ = *from++;
	case 4:		*to++ = *from++;
	case 3:		*to++ = *from++;
	case 2:		*to++ = *from++;
	case 1:		*to++ = *from++;
		}while(--n>0);
	}
</pre>
ให้ นศ ศึกษาและอธิบายว่า ทำไม  Dusff  code จึงสามารถก๊อปปี้ค่า  array   ได้อย่างถูกต้อง  และทำไมจึงไม่ผิด syntax ของภาษา C 
<p>
<p>
<b>References</b>
<p>
<ul>
<li>[1] <a href="http://www.lysator.liu.se/c/duffs-device.html">Duff's Device Email</a>
</ul>
