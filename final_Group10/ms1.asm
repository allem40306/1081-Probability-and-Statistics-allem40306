#include <iostream>
using namespace std;
const int N = 100;
int arr[N], buf[N];
void sol(int L, int R) {
00C022A0  push        ebp  
00C022A1  mov         ebp,esp  
00C022A3  sub         esp,0FCh  
00C022A9  push        ebx  
00C022AA  push        esi  
00C022AB  push        edi  
00C022AC  lea         edi,[ebp-0FCh]  
00C022B2  mov         ecx,3Fh  
00C022B7  mov         eax,0CCCCCCCCh  
00C022BC  rep stos    dword ptr es:[edi]  
	if (R - L <= 1)return;
00C022BE  mov         eax,dword ptr [R]  
00C022C1  sub         eax,dword ptr [L]  
00C022C4  cmp         eax,1  
00C022C7  jg          sol+2Eh (0C022CEh)  
00C022C9  jmp         sol+15Fh (0C023FFh)  
	int M = (R + L) / 2;
00C022CE  mov         eax,dword ptr [R]  
00C022D1  add         eax,dword ptr [L]  
00C022D4  cdq  
00C022D5  sub         eax,edx  
00C022D7  sar         eax,1  
00C022D9  mov         dword ptr [M],eax  
00C022DC  ?? ?? 
00C022DD  ?? ?? 
00C022DE  ?? ?? 
00C022DF  ?? ?? 
00C022E0  ?? ?? 
00C022E1  ?? ?? 
00C022E2  ?? ?? 
00C022E3  ?? ?? 
00C022E4  ?? ?? 
00C022E5  ?? ?? 
00C022E6  ?? ?? 
00C022E7  ?? ?? 
00C022E8  ?? ?? 
00C022E9  ?? ?? 
00C022EA  ?? ?? 
00C022EB  ?? ?? 
00C022EC  ?? ?? 
00C022ED  ?? ?? 
00C022EE  ?? ?? 
00C022EF  ?? ?? 
00C022F0  ?? ?? 
00C022F1  ?? ?? 
00C022F2  ?? ?? 
00C022F3  ?? ?? 
00C022F4  ?? ?? 
	sol(M, R);
00C022F5  shr         ch,0FFh  
00C022F8  inc         dword ptr [ebx+458B08C4h]  
	int i = L, j = M, k = L;
00C022FE  or          byte ptr [ecx+458BEC45h],cl  
00C02304  clc  
00C02305  mov         dword ptr [j],eax  
00C02308  mov         eax,dword ptr [L]  
00C0230B  mov         dword ptr [k],eax  
	while (i < M || j < R) {
00C0230E  mov         eax,dword ptr [i]  
00C02311  cmp         eax,dword ptr [M]  
00C02314  jl          sol+82h (0C02322h)  
00C02316  mov         eax,dword ptr [j]  
00C02319  cmp         eax,dword ptr [R]  
00C0231C  jge         sol+130h (0C023D0h)  
		if (i >= M)
00C02322  mov         eax,dword ptr [i]  
00C02325  cmp         eax,dword ptr [M]  
00C02328  jl          sol+0A9h (0C02349h)  
			buf[k] = arr[j++];
00C0232A  mov         eax,dword ptr [k]  
00C0232D  mov         ecx,dword ptr [j]  
00C02330  mov         edx,dword ptr arr (0C0B138h)[ecx*4]  
00C02337  mov         dword ptr buf (0C0B2C8h)[eax*4],edx  
00C0233E  mov         eax,dword ptr [j]  
00C02341  add         eax,1  
00C02344  mov         dword ptr [j],eax  
00C02347  jmp         sol+122h (0C023C2h)  
		else if (j >= R)
00C02349  mov         eax,dword ptr [j]  
00C0234C  cmp         eax,dword ptr [R]  
00C0234F  jl          sol+0D0h (0C02370h)  
			buf[k] = arr[i++];
00C02351  mov         eax,dword ptr [k]  
00C02354  mov         ecx,dword ptr [i]  
			buf[k] = arr[i++];
00C02357  mov         edx,dword ptr arr (0C0B138h)[ecx*4]  
00C0235E  mov         dword ptr buf (0C0B2C8h)[eax*4],edx  
00C02365  mov         eax,dword ptr [i]  
00C02368  add         eax,1  
00C0236B  mov         dword ptr [i],eax  
		else {
00C0236E  jmp         sol+122h (0C023C2h)  
			if (arr[i] <= arr[j])
00C02370  mov         eax,dword ptr [i]  
00C02373  mov         ecx,dword ptr [j]  
00C02376  mov         edx,dword ptr arr (0C0B138h)[eax*4]  
00C0237D  cmp         edx,dword ptr arr (0C0B138h)[ecx*4]  
00C02384  jg          sol+105h (0C023A5h)  
				buf[k] = arr[i++];
00C02386  mov         eax,dword ptr [k]  
00C02389  mov         ecx,dword ptr [i]  
00C0238C  mov         edx,dword ptr arr (0C0B138h)[ecx*4]  
00C02393  mov         dword ptr buf (0C0B2C8h)[eax*4],edx  
00C0239A  mov         eax,dword ptr [i]  
00C0239D  add         eax,1  
00C023A0  mov         dword ptr [i],eax  
			else {
00C023A3  jmp         sol+122h (0C023C2h)  
				buf[k] = arr[j++];
00C023A5  mov         eax,dword ptr [k]  
00C023A8  mov         ecx,dword ptr [j]  
00C023AB  mov         edx,dword ptr arr (0C0B138h)[ecx*4]  
00C023B2  mov         dword ptr buf (0C0B2C8h)[eax*4],edx  
00C023B9  mov         eax,dword ptr [j]  
00C023BC  add         eax,1  
00C023BF  mov         dword ptr [j],eax  
			}
		}
		k++;
00C023C2  mov         eax,dword ptr [k]  
			}
		}
		k++;
00C023C5  add         eax,1  
00C023C8  mov         dword ptr [k],eax  
	}
00C023CB  jmp         sol+6Eh (0C0230Eh)  
	for (int k = L; k < R; k++) arr[k] = buf[k];
00C023D0  mov         eax,dword ptr [L]  
00C023D3  mov         dword ptr [ebp-38h],eax  
00C023D6  jmp         sol+141h (0C023E1h)  
00C023D8  mov         eax,dword ptr [ebp-38h]  
00C023DB  add         eax,1  
00C023DE  mov         dword ptr [ebp-38h],eax  
00C023E1  mov         eax,dword ptr [ebp-38h]  
00C023E4  cmp         eax,dword ptr [R]  
00C023E7  jge         sol+15Fh (0C023FFh)  
00C023E9  mov         eax,dword ptr [ebp-38h]  
00C023EC  mov         ecx,dword ptr [ebp-38h]  
00C023EF  mov         edx,dword ptr buf (0C0B2C8h)[ecx*4]  
00C023F6  mov         dword ptr arr (0C0B138h)[eax*4],edx  
00C023FD  jmp         sol+138h (0C023D8h)  
	return;
}
00C023FF  pop         edi  
00C02400  pop         esi  
00C02401  pop         ebx  
00C02402  add         esp,0FCh  
00C02408  cmp         ebp,esp  
00C0240A  call        __RTC_CheckEsp (0C0114Ah)  
00C0240F  mov         esp,ebp  
00C02411  pop         ebp  
00C02412  ret  
00C02413  int         3  
00C02414  int         3  
00C02415  int         3  
00C02416  int         3  
00C02417  int         3  
00C02418  int         3  
00C02419  int         3  
00C0241A  int         3  
00C0241B  int         3  
00C0241C  int         3  
00C0241D  int         3  
00C0241E  int         3  
00C0241F  int         3  
00C02420  int         3  
00C02421  int         3  
00C02422  int         3  
00C02423  int         3  
00C02424  int         3  
00C02425  int         3  
00C02426  int         3  
00C02427  int         3  
00C02428  int         3  
00C02429  int         3  
00C0242A  int         3  
00C0242B  int         3  
00C0242C  int         3  
00C0242D  int         3  
00C0242E  int         3  
00C0242F  int         3  
00C02430  int         3  
00C02431  int         3  
00C02432  int         3  
00C02433  int         3  
00C02434  int         3  
00C02435  int         3  
00C02436  int         3  
00C02437  int         3  
00C02438  int         3  
00C02439  int         3  
00C0243A  int         3  
00C0243B  int         3  
00C0243C  int         3  
00C0243D  int         3  
00C0243E  int         3  
00C0243F  int         3  
00C02440  int         3  
00C02441  int         3  
00C02442  int         3  
00C02443  int         3  
00C02444  int         3  
00C02445  int         3  
00C02446  int         3  
00C02447  int         3  
00C02448  int         3  
00C02449  int         3  
00C0244A  int         3  
00C0244B  int         3  
00C0244C  int         3  
00C0244D  int         3  
00C0244E  int         3  
00C0244F  int         3  
00C02450  int         3  
00C02451  int         3  
00C02452  int         3  
00C02453  int         3  
00C02454  int         3  
00C02455  int         3  
00C02456  int         3  
00C02457  int         3  
00C02458  int         3  
00C02459  int         3  
00C0245A  int         3  
00C0245B  int         3  
00C0245C  int         3  
00C0245D  int         3  
00C0245E  int         3  
00C0245F  int         3  
00C02460  int         3  
00C02461  int         3  
00C02462  int         3  
00C02463  int         3  
00C02464  int         3  
00C02465  int         3  
00C02466  int         3  
00C02467  int         3  
00C02468  int         3  
00C02469  int         3  
00C0246A  int         3  
00C0246B  int         3  
00C0246C  int         3  
00C0246D  int         3  
00C0246E  int         3  
00C0246F  int         3  
--- c:\users\nt2018\documents\visual studio 2017\projects\project1\project1\source.cpp 

int main() {
00C02470  push        ebp  
00C02471  mov         ebp,esp  
00C02473  sub         esp,0E8h  
00C02479  push        ebx  
00C0247A  push        esi  
00C0247B  push        edi  
00C0247C  lea         edi,[ebp-0E8h]  
00C02482  mov         ecx,3Ah  
00C02487  mov         eax,0CCCCCCCCh  
00C0248C  rep stos    dword ptr es:[edi]  
00C0248E  mov         eax,dword ptr [__security_cookie (0C0B004h)]  
00C02493  xor         eax,ebp  
00C02495  mov         dword ptr [ebp-4],eax  
	int n;
	cin >> n;
00C02498  mov         esi,esp  
00C0249A  lea         eax,[n]  
00C0249D  push        eax  
00C0249E  mov         ecx,dword ptr [_imp_?cin@std@@3V?$basic_istream@DU?$char_traits@D@std@@@1@A (0C0C09Ch)]  
00C024A4  call        dword ptr [__imp_std::basic_istream<char,std::char_traits<char> >::operator>> (0C0C0A0h)]  
00C024AA  cmp         esi,esp  
00C024AC  call        __RTC_CheckEsp (0C0114Ah)  
	for (int i = 0; i<n; i++) {
00C024B1  mov         dword ptr [ebp-18h],0  
00C024B8  jmp         main+53h (0C024C3h)  
00C024BA  mov         eax,dword ptr [ebp-18h]  
00C024BD  add         eax,1  
00C024C0  mov         dword ptr [ebp-18h],eax  
00C024C3  mov         eax,dword ptr [ebp-18h]  
00C024C6  cmp         eax,dword ptr [n]  
00C024C9  jge         main+7Dh (0C024EDh)  
		cin >> arr[i];
00C024CB  mov         eax,dword ptr [ebp-18h]  
00C024CE  lea         ecx,arr (0C0B138h)[eax*4]  
00C024D5  mov         esi,esp  
00C024D7  push        ecx  
00C024D8  mov         ecx,dword ptr [_imp_?cin@std@@3V?$basic_istream@DU?$char_traits@D@std@@@1@A (0C0C09Ch)]  
00C024DE  call        dword ptr [__imp_std::basic_istream<char,std::char_traits<char> >::operator>> (0C0C0A0h)]  
00C024E4  cmp         esi,esp  
00C024E6  call        __RTC_CheckEsp (0C0114Ah)  
	}
00C024EB  jmp         main+4Ah (0C024BAh)  
	sol(0, n - 1);
00C024ED  mov         eax,dword ptr [n]  
00C024F0  sub         eax,1  
00C024F3  push        eax  
00C024F4  push        0  
00C024F6  call        sol (0C010B9h)  
00C024FB  add         esp,8  
	for (int i = 0; i<n; i++) {
00C024FE  mov         dword ptr [ebp-24h],0  
00C02505  jmp         main+0A0h (0C02510h)  
00C02507  mov         eax,dword ptr [ebp-24h]  
00C0250A  add         eax,1  
00C0250D  mov         dword ptr [ebp-24h],eax  
00C02510  mov         eax,dword ptr [ebp-24h]  
00C02513  cmp         eax,dword ptr [n]  
00C02516  jge         main+0D5h (0C02545h)  
		cout << arr[i] << ' ';
00C02518  push        20h  
00C0251A  mov         esi,esp  
00C0251C  mov         eax,dword ptr [ebp-24h]  
00C0251F  mov         ecx,dword ptr arr (0C0B138h)[eax*4]  
00C02526  push        ecx  
00C02527  mov         ecx,dword ptr [_imp_?cout@std@@3V?$basic_ostream@DU?$char_traits@D@std@@@1@A (0C0C098h)]  
00C0252D  call        dword ptr [__imp_std::basic_ostream<char,std::char_traits<char> >::operator<< (0C0C0A8h)]  
00C02533  cmp         esi,esp  
00C02535  call        __RTC_CheckEsp (0C0114Ah)  
00C0253A  push        eax  
00C0253B  call        std::operator<<<std::char_traits<char> > (0C012C1h)  
00C02540  add         esp,8  
	}
00C02543  jmp         main+97h (0C02507h)  
	cout << '\n';
00C02545  push        0Ah  
00C02547  mov         eax,dword ptr [_imp_?cout@std@@3V?$basic_ostream@DU?$char_traits@D@std@@@1@A (0C0C098h)]  
00C0254C  push        eax  
00C0254D  call        std::operator<<<std::char_traits<char> > (0C012C1h)  
00C02552  add         esp,8  
}
00C02555  xor         eax,eax  
00C02557  push        edx  
00C02558  mov         ecx,ebp  
00C0255A  push        eax  
00C0255B  lea         edx,ds:[0C02588h]  
00C02561  call        @_RTC_CheckStackVars@8 (0C012ADh)  
00C02566  pop         eax  
00C02567  pop         edx  
00C02568  pop         edi  
00C02569  pop         esi  
}
00C0256A  pop         ebx  
00C0256B  mov         ecx,dword ptr [ebp-4]  
00C0256E  xor         ecx,ebp  
00C02570  call        @__security_check_cookie@4 (0C012C6h)  
00C02575  add         esp,0E8h  
00C0257B  cmp         ebp,esp  
00C0257D  call        __RTC_CheckEsp (0C0114Ah)  
00C02582  mov         esp,ebp  
00C02584  pop         ebp  
00C02585  ret  
00C02586  xchg        ax,ax  
00C02588  add         dword ptr [eax],eax  
00C0258A  add         byte ptr [eax],al  
00C0258C  nop  
00C0258D  and         eax,0FFF400C0h  
00C02592  ?? ?? 
00C02593  inc         dword ptr [eax+eax]  
00C02596  add         byte ptr [eax],al  
00C02598  pushfd  
00C02599  and         eax,6E00C0h 