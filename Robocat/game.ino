void Sansukumi_ken() {
  for (int i = 3; i>0; i--) {
    Text(String(i));
    delay(1000);
  };
  Text("Let's go!");
  Text("I'm first!");
  delay(3000);
  int tomo = random(1, 4);
  Text("I have...");
  choise(tomo);
  int master = random(1,4);
  Text("You choose");
  choise(master);
  if ((tomo == 1 && master == 2)||(tomo == 2 && master == 3)||(tomo == 3 && master==1)){
    Text("Nya! ^^");
    mood += 30;
  };
  if ((tomo == 1 && master == 3)||(tomo == 2 && master == 1)||(tomo == 3 && master == 2)){
    Text("You win o(T_To)");
    mood -= 10;
  };
  if ((tomo == 1 && master == 1)||(tomo==2 && master == 2)||(tomo == 3 && master == 3)){
    Text("The friendship wins!");
    mood += 10;
  };
  proc();
};
void choise (int player){
  switch (player){
    case 1: Text("a stone"); break;
    case 2: Text("scissors"); break;
    case 3: Text("paper"); break;
    default: Text("Something went wrong. Contact on GitHub. Just a mistake");
  };
};

