using namespace std;

class Animal {
public:
	Animal(const string& name);

	//accessors
	const string& getName() const; 
	int getWeight() const; 
	bool getLand() const;
	bool getWater() const;
	bool getMeat() const;
	bool getPlants() const;
	bool isOmnivore() const;
	bool isAmphibious() const;

	//modifiers
	void setName(const string& n);
	int setWeight(int weight);
	bool setLand(bool land);
	bool setWater(bool water);
	bool setMeat(bool meat);
	bool setPlants(bool plants);

private:
	string name;
	int weight;
	bool land;
	bool water;
	bool meat;
	bool plants;
};