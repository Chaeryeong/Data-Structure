import java.util.*;

/*
 계수나 차수가 float과  integer 범위를 벗어나는 것에 대해서는 고려를 해주지 않았습니다.
수업시간에 간단한 차수와 계수에 대해 연산할 것이라고 언급해주셨고, 어차피 범위를 벗어난 것에 대해서는 저장하는 것이 오류가 나기 때문입니다.
 */

public class Padd {
	
	/*이 class의 모든 method들이 공유하는 field*/
	
	static int MAX_TERM = 100; /* 배열이 너무 커지는 것을 막기 위함, 항의 개수에 제한 */
	static Poly poly[] = new Poly[MAX_TERM]; /* MAX_TERM개의 Poly 데이터 타입을 가지는 배열 선언 - 두 다항식과 결과 다항식 함께 저장 */
	static int avail = 0; /* 배열 poly에서 다음 값을 저장할 수 있는 사용 가능한 인덱스 */
	static int startA, startB, finishA, finishB; /* 각 다항식을 공유되는 한 배열에 저장하기 위해서, 각 다항식의 시작과 끝 인덱스를 변수로 둠 */
	static int startD, finishD; /* A(x)와 B(x)를 더한 결과 다항식인 D(x)가 poly 배열에 저장되는 시작과 끝 인덱스  */
	

	public static void main(String[] args) {
		
	/* main 메서드에서는 두 다항식을 입력받아 공유하는 배열에 저장하고, 덧셈을 해주는 padder 메서드를 호출함 */
		
		/* NullPointerEXCEPTION을 방지하기위해 배열 안의 각 object를 초기화 */
		for(int i = 0; i<poly.length; i++) {
			poly[i] = new Poly();
		} 
		
		/* 사용자로부터 입력을 받기 위해 Scanner 객체 생성 */
		Scanner scan = new Scanner(System.in);
		
		System.out.println("첫번쨰 다항식을 입력하세요.");
		
		String temp; /* 한 다항식을 string으로 입력받기 위해 string 변수 선언 */
		temp = scan.nextLine();
		
		/* 아무것도 입력하지 않고 엔터(개행)를 누를 경우에 대한 예외 처리 */
		if(temp.equals("")) { 
			System.out.println("다항식을 입력하지 않아서 종료합니다.");
			System.exit(1);
		}
		
		/* string으로 입력받은 다항식을 배열에 저장하기 위해서 공백을 구분자로 잘라서 임시 배열에 저장 */
		String arr[] = temp.split(" "); 
		
		/* 계수와 지수 짝이 맞지 않는 경우에 대한 예외처리 */
		if(arr.length%2 != 0) {
			System.out.println("계수와 지수의 짝이 맞지 않아서 종료합니다.");
			System.exit(1);
		}
		
		startA = avail; /* 첫번째 다항식을 poly 배열에 저장을 시작할 수 있는 위치 */
		
		/* arr배열에서 계수와 차수를 poly배열에 저장, arr배열에는 계수와 차수가 입력 순서대로 저장되어 있음 */
		for(int i = 0; i<arr.length ;avail++) {
			poly[avail].coef = Float.parseFloat(arr[i]); 
			i++;
			poly[avail].expon = Integer.parseInt(arr[i]);
			i++;
			}
		
		finishA = avail-1; 
		
		/* poly 배열에 최종적으로 값을 저장하기위해 사용한 string과 배열의 reference를 clear해줌
		   나중에 garbage로 처리가 됨
		   => C언어의 free()를 대체하기 위함임 */
		temp = null; 
		arr = null;
		
		System.out.println("두번쨰 다항식을 입력하세요.");
		
		startB = avail; /* 두번째 다항식을 poly 배열에 저장을 시작할 수 있는 위치 */
		
		String temp2 = scan.nextLine(); 
		
		if(temp2.equals("")) {
			System.out.println("다항식을 입력하지 않아서 종료합니다.");
			System.exit(1);
		}
		
		String arr2[] = temp2.split(" "); 
		
		/* 계수와 지수 짝이 맞지 않는 경우에 대한 예외처리 */
		if(arr2.length%2 != 0) {
			System.out.println("계수와 지수의 짝이 맞지 않아서 종료합니다.");
			System.exit(1);
		}
		
		for(int i = 0; i<arr2.length ;avail++) {
			poly[avail].coef = Float.parseFloat(arr2[i]); 
			i++;
			poly[avail].expon = Integer.parseInt(arr2[i]);
			i++;
			}
		
		finishB = avail-1;
		
		temp2 = null;
		arr2 = null;
		
		/* 두개의 다항식 덧셈 함수 호출 */
		padder();
		
		/* garbage collector로 free space를 reclaim해줌 */
		System.gc(); 
			
	} // main 메소드의 끝
	
	
	static void padder() {
	
	/* padder 메소드에서는 A(x)+B(x)의 결과인 D(x)를 계산하기 위한 함수들을 호출하고 인덱스들을 조정하며, D(x)를 출력함  */
		
		startD = avail;
		float coefficient;
		
		/* 두 다항식의 차수를 비교하며 연산하는 부분 */
		while(startA<=finishA && startB<=finishB) {
			switch(compare(poly[startA].expon, poly[startB].expon)) { // A(x)와 B(x)의 항의 차수를 비교
				case -1: // A expon < b expon 때, B(x) 항을 D(x)에 넣음
					attach(poly[startB].coef, poly[startB].expon);
					startB++;
					break;
				case 0: // A expon == b expon 때, 두 다항식의 동차항읙 계수를 더해서 D(x)에 넣음
					coefficient = poly[startA].coef + poly[startB].coef;
					if (coefficient !=0 ) { // 두 계수의 합이 0이라면 D(x)에 굳이 저장하지 않아도 됨
						attach(coefficient, poly[startA].expon);
					}
					startA++;
					startB++;
					break;
				case 1: //// A expon > b expon 때, A(x)의 항을 D(x)에 넣음
					attach(poly[startA].coef, poly[startA].expon);
					startA++;
			} // switch 문의 끝
		} // while 문의 끝
		
		/* 두 다항식의 차수를 비교하면서 D(x)에 값을 넣는 연산이 끝난 후, 남은 한 다항식의 항들을 D(x)에 넣어줌 */
			/* A(x)의 남은 항을 D(x)에 넣음 */
		for(; startA<=finishA; startA++) {
			attach(poly[startA].coef, poly[startA].expon);
		}
			/* B(x)의 남은 항을 D(x)에 넣음 */
		for(; startB<=finishB; startB++) {
			attach(poly[startB].coef, poly[startB].expon);
		}
		
		finishD = avail-1;
		
		/* poly 배열에 저장된 D(x)를 출력 */
		for(int i = startD; i<=finishD; i++) {
			if(i==finishD) { // 마지막 항일 경우 뒤에 덧셈 기호가 필요 없음
				if(poly[i].expon == 0) { // 상수항일 경우 계수만 출력
					System.out.printf("%.3f", poly[i].coef); // 계수는 소수점 아래 3자리까지 출력
				}
				else { // 상수항은 아니지만 D(x)의 마지막 항일 경우
					System.out.printf("%.3f", poly[i].coef);
					System.out.print("x^"+poly[i].expon);
				}
			}
			else{ // 마지막 항이 아닐 경우, 뒤에 덧셈 기호가 필요함
				System.out.printf("%.3f", poly[i].coef);
				System.out.print("x^"+poly[i].expon+ " + ");
			}
		} // for 문의 끝
		
	} // padder 메소드의 끝
	
	
	static int compare(int x, int y) {
		
	/* compare 메소드에서는 두 다항식의 항의 계수를 비교해서 결과를 정수로 반환함 */
		
		/* case analysis
		 x<y -> z = -1
		 x==y -> z = 0
		 x>y -> z = 1
		 */
		int z = (((x) < (y))? -1: ((x)==(y)) ? 0 : 1);
		
		return z;
	} // compare 메소드의 끝
	
	
	static void attach(float coefficient, int exponent) {
		
	/* attach 메소드에서는 padder 메소드로부터 결과 다항식인 D(x)에 넣을 각 항의 계수와 차수를 넘겨 받아 poly 배열에 저장함 */
		
		/* 두 항의 연산 결과를 저장할 시, poly 배열의 최대 저장 가능한 항 개수를 넘으면 프로그램을 종료함
		   ArrayOutOfBoundEXCEPTION을 미리 방지하기 위함 */
		if(avail>=MAX_TERM) {
			System.out.println("Too many terms in the polynomial!");
			System.exit(1);
		}
		
		/* 계수가 0이 아닐 때만 저장하고, 0일 때는 저장하지 않고 padder 메소드로 돌아감*/
		if(coefficient!=0) {
		poly[avail].coef = coefficient;
		poly[avail].expon = exponent;
		avail++;
		}
		
	} // attach 메소드의 끝
	

} // Padd 클래스의 끝


/* C언어의 typedef struct 역할
   계수와 차수를 하나의 객체로 만들어서 배열에 저장하기 위함 */
class Poly{
	float coef; // ADT에 따라 계수는 실수, 차수는 정수로 선언함
	int expon;
}

/* 고맙습니다 :) */
