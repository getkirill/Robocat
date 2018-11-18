void info(float a, int b, int c) {
  Text("Therm:");
  Text(String(a));
  Text("Lighting:");
  Text(String(b));
  Text("Noise level:");
  if (c < 300) {
    Text("quiet");
  };
  if ((c >= 300) && (c < 450)) {
    Text("fine");
  };
  if (c >= 450) {
  Text("loud");
  };
  whatDay(a, b, c);
};
void feed() {
  if (satiety < 100) {
    satiety += 35;
  }
  else {
    health -= 5;
  };
  Text("Chomp-chomp..");
  proc();
};
void tablet() {
  if (mood > 80) {
    health += 15;
    Text("Mr-r. I'm fine now");
  }
  else {
    Text("NO!I don't want!");
  };
  proc();
};
void bath() {
  if (mood >= 50) {
    health += 10;
    mood += 10;
    Text("*shining like the sun*");
  }
  else {
    Text("NO!I don't want!");
  };
  proc();
};
void cookie() {
  mood += 20;
  satiety += 5;
  health -= 5;
  Text("Thanks you!I like it.");
  //Text("Thanks you!I like eat");
  proc();
};
void punishment() {
  mood -= 15;
  Text("*Crying*");
  proc();
};
void pet() {
  Text("Health:"); Text(String(health));
  Text("Satiety:"); Text(String(satiety));
  Text("Mood:"); Text(String(mood));
};
void whatDay(float a, int b, int c) {
  if (a > 20.0){
    Text("a warm ");
  }
  else{
    Text("a cold ");
  };
  if (c < 300) {
    Text("quiet ");
  }
  else{
    Text("loud ");
  };
  if (b > 200) {
    Text("day");
  }
  else{
    Text("evening");
  };
};
void proc(){
  if (satiety > 100) satiety = 100;
  if (mood > 100) mood = 100;
  if (health > 100) health = 100;
  if (satiety <= 0) satiety = 0;
  if (mood <= 0) mood = 0;
  if (health <= 0) health = 0;
};

