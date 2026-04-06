#pragma once
#include <string>

using namespace std;

class StudentInfo {
public:
	enum BeltRank //skill of student
	{
		White, 
		Yellow, 
		Green, 
		Blue, 
		Purple, 
		Brown, 
		Black
	};

	enum BeltStripes { //how far along the belt they are
		zero,
		one, 
		two, 
		three, 
		four
	};

	// create a struct that holds all student info
	struct StudentInf {
		string name;
		int age; //will change this later to check if the age is above or equal to 6
		//string startDate;  //01/22/2026
		bool isReturning;
		int monthsEnrolled;
		BeltRank rank; //use the enum here, white
		BeltStripes stripes; //zero
		//double balance;
		bool needsGear;
		string Contact;

		StudentInf() :
			name(""), age(6),
			isReturning(false), monthsEnrolled(0),
			rank(White), stripes(zero),
			//balance(0.0),
			needsGear(false),
			Contact("")
		{
			//nothing!
		}
	};

	StudentInfo();
	StudentInfo(const string&, int, bool, int, BeltRank, BeltStripes, bool, const string&);

	virtual ~StudentInfo();

	// --- Base Class ---
	// Requirements: String, Int, Enum, Protected member, Virtual print,
	//Constructors.

    // Getters and Setters
	void setName(const string&);
	const string& getName() const;

	void setAge(int);
	int getAge() const;

	void setMonths(int);
	int getMonths() const;

	void setReturning(bool);
	bool getReturning() const;

	void setRank(BeltRank);
	BeltRank getRank() const;

	void setStripes(BeltStripes);
	BeltStripes getStripes() const;

	void setGear(bool);
	bool getGear() const;

	void setContact(const string&);
	const string& getContact() const;

	virtual void print() const;

	virtual void toStream(ostream&) const;
	virtual double getvalue() const = 0;

	protected:
		// Protected: derived classes need access
		int MonthsEnrolled;
		string Name; //change to first and last name when you have the mental cap
		static const char* BeltRankstring(BeltRank);
		static const char* BeltStripesstring(BeltStripes);
	private:
		int Age;
		bool IsReturning;
		//double Balance;
		bool NeedsGear;
		string ECon;
		BeltRank Rank;
		BeltStripes Stripes;

};

ostream& operator<<(ostream&, const StudentInfo&);