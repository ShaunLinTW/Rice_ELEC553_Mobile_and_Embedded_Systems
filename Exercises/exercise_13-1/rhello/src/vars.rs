pub fn run(){
	let name = "Shaun";
	// let mut age = 24;
	// age = 25;
	// println!("{}",age);
	let mut a: i32 = 5;
	// a = 5;
	println!("a is: {}", a);
	let (x, y) = ("Shaun", -1000);
	println!("{} {}", x, y);
	println!("{}", '\u{1F600}'); // print the moji
	
	// Arrays
	let mut numbers_arr: [i32; 4] = [1, 2, 3, 4];
	numbers_arr[2] = 20;
	println!("{:?}", numbers_arr);

	// Get slice
	let slice: &[i32] = &numbers_arr[1..=3];
	println!("{:?}", slice);
}
