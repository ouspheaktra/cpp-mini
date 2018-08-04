#pragma once

#include "resource.h"
#include <windows.h>

class Stop;

class Passenger {
	int waitMinutes;
	Stop *destination;
	bool waiting;
public:
	Passenger() : waitMinutes(0), waiting(true) { }

	void SetDestination(Stop *stop) {
		destination = stop;
	}
	Stop *GetDestination() {
		return destination;
	}
	int GetWaitMinutes() {
		return waitMinutes;
	}
	void EnterTheBus() {
		waiting = false;
	}
	bool isWaiting() {
		return waiting;
	}

	void Wait(int minutes) {
		waitMinutes += minutes;
	}
};

class Stop {
	Passenger **passengers;
	int passengersAmount;
	Point coord;
public:
	int id;
	Stop() : passengersAmount(0), passengers(NULL) {};

	void SetCoordXY(int x, int y) {
		coord.x = x;
		coord.y = y;
	}
	void SetCoord(Point coord) {
		this->coord = coord;
	}
	int GetPassengersAmount() {
		return passengersAmount;
	}
	Passenger *GetPassenger(int id) {
		return passengers[id];
	}
	Point GetCoord() {
		return coord;
	}

	void AddPassenger(Passenger *passenger) {
		Passenger **temp = new Passenger*[passengersAmount + 1];
		for (int i = 0; i < passengersAmount; i++)
			temp[i] = passengers[i];
		temp[passengersAmount] = passenger;
		delete[] passengers;
		passengers = temp;
		passengersAmount++;
	}
	Passenger *ExtractPassenger() {
		if (passengersAmount == 0)
			return NULL;
		Passenger *passenger = passengers[0];
		for (int i = 1; i < passengersAmount; i++)
			passengers[i - 1] = passengers[i];
		passengersAmount--;
		return passenger;
	}
};

class Route {
	Stop **stops;
	int stopsAmount;
public:
	Route() : stops(NULL), stopsAmount(0) { }

	int GetStopsAmount() {
		return stopsAmount;
	}
	Stop *GetStop(int id) {
		return stops[id];
	}
	Stop **GetStops() {
		return stops;
	}

	void AddStop(Stop *stop) {
		Stop **temp = new Stop*[stopsAmount + 1];
		for (int i = 0; i < stopsAmount; i++)
			temp[i] = stops[i];
		temp[stopsAmount] = stop;
		delete[] stops;
		stops = temp;
		stopsAmount++;
	}
	Stop *AfterThisStop(Stop *stop) {
		for (int i = 0; i < stopsAmount; i++)
			if (stops[i] == stop)
				if (i + 1 < stopsAmount)
					return stops[i + 1];
				else
					break;
		return NULL;
	}
};

class Bus {
	int seatAmount;
	int speed;
	Passenger **passengers;
	int passengersAmount;
	Route *route;
	Stop *from, *to;
	double percentageToNextStop;
	bool going;
public:
	Bus() : seatAmount(0), passengers(NULL), going(false) { };
	
	void SetSeatAmount(int seatAmount) {
		this->seatAmount = seatAmount;
	};
	void SetRoute(Route *route) {
		this->route = route;
		from = route->GetStop(0);
		to = route->GetStop(0);
		percentageToNextStop = 0;
	}
	int GetSeatAmount() {
		return seatAmount;
	}
	int GetPassengersAmount() {
		return passengersAmount;
	}
	Stop *GetNextStop() {
		return to;
	}
	Stop *GetPreviousStop() {
		return from;
	}
	bool isGoing() {
		return going;
	}
	void Start() {
		from = route->GetStop(0);
		to = route->AfterThisStop(from);
		going = true;
	}

	Point GetCoord() {
		Point s1 = from->GetCoord();
		if (!going)
			return s1;
		Point s2 = to->GetCoord();
		Point p;
		p.x = s1.x + (s2.x - s1.x)*percentageToNextStop;
		p.y = s1.y + (s2.y - s1.y)*percentageToNextStop;
		return p;
	}

	void AddPassenger(Passenger *passenger) {
		if (!passenger)
			return;
		Passenger **temp = new Passenger*[passengersAmount + 1];
		for (int i = 0; i < passengersAmount; i++)
			temp[i] = passengers[i];
		temp[passengersAmount] = passenger;
		delete[] passengers;
		passengers = temp;
		passengersAmount++;
	}
	void ExtractPassenger(Passenger *passenger) {
		bool found = false;
		for (int i = 0; i < passengersAmount; i++) {
			if (passengers[i] == passenger)
				found = true;
			if (found && i+i < passengersAmount)
				passengers[i] = passengers[i + 1];
		}
		passengersAmount--;
	}
	void AtStop() {
		// if passengers want to leave
		for (int i = 0; i < passengersAmount; i++)
			if (from == passengers[i]->GetDestination())
				ExtractPassenger(passengers[i--]);
		// passengers enter the bus
		Passenger *passenger;
		while (passengersAmount < seatAmount && (passenger = from->ExtractPassenger())) {
			AddPassenger(passenger);
			passenger->EnterTheBus();
		}
	}
	void Move(double percentage) {
		if (!isGoing())
			return;
		percentageToNextStop += percentage;
		// bus at stop
		if (percentageToNextStop >= 1) {
			percentageToNextStop = 0;
			from = to;
			to = route->AfterThisStop(from);
			if (!to)
				going = false;
			AtStop();
		}
	}
};