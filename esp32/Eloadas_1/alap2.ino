class hetfo
{
  public:
    int a = 1;
    int b = 2;
    int c = 3;

    //char *tomb = "hetfo";
};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(ESP.getChipModel());
  Serial.println(ESP.getChipCores());
  Serial.println(ESP.getFlashChipSize());

  hetfo h;

  Serial.println(h.a);
  h.a = 123;
  Serial.println(h.a);

}

void loop() {
  // put your main code here, to run repeatedly:

/*
  for(int a=0; a<200; a++)
  {
    Serial.println(random(1,100));
  }
*/



}
