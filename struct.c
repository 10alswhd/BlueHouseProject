#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <omp.h>

struct SystemState {
	double rx,ry,rz;
	double vx,vy,vz;
};
struct SystemDerivative {
	double drx,dry,drz;
	double dvx,dvy,dvz;
};

typedef struct SystemState State;
typedef struct SystemDerivative Derivative;

Derivative evaluate(State initial, Derivative d, double t, double dt);
State rk_integrate(State state, double t, double dt);
State ee_integrate(State state, double t, double dt);
State EEuler(State state, double t0, double t1, double dt);
State RK4(State state, double t0, double t1, double dt);
double acceleration_x(State state, double t);
double acceleration_y(State state, double t);
double acceleration_z(State state, double t);

Derivative evaluate(State initial, Derivative d, double t, double dt) {
	State state;

	state.rx = initial.rx + d.drx*dt;
	state.ry = initial.ry + d.dry*dt;
	state.rz = initial.rz + d.drz*dt;
	state.vx = initial.vx + d.dvx*dt;
	state.vy = initial.vy + d.dvy*dt;
	state.vz = initial.vz + d.dvz*dt;

	Derivative output;
	output.drx = state.vx;
	output.dry = state.vy;
	output.drz = state.vz;
	output.dvx = acceleration_x(state, t+dt);
	output.dvy = acceleration_y(state, t+dt);
	output.dvz = acceleration_z(state, t+dt);
	return output;
}

State rk_integrate(State state, double t, double dt) {
	Derivative zeroth;
	Derivative a = evaluate(state, zeroth, t, 0.0);
	Derivative b = evaluate(state, a, t, dt*0.5);
	Derivative c = evaluate(state, b, t, dt*0.5);
	Derivative d = evaluate(state, c, t, dt);

	const double drxdt = 1.0/6.0 * (a.drx + 2.0*(b.drx+c.drx) + d.drx);
	const double dvxdt = 1.0/6.0 * (a.dvx + 2.0*(b.dvx+c.dvx) + d.dvx);
	const double drydt = 1.0/6.0 * (a.dry + 2.0*(b.dry+c.dry) + d.dry);
	const double dvydt = 1.0/6.0 * (a.dvy + 2.0*(b.dvy+c.dvy) + d.dvy);
	const double drzdt = 1.0/6.0 * (a.drz + 2.0*(b.drz+c.drz) + d.drz);
	const double dvzdt = 1.0/6.0 * (a.dvz + 2.0*(b.dvz+c.dvz) + d.dvz);

	state.rx = state.rx + drxdt*dt;
	state.vx = state.vx + dvxdt*dt;
	state.ry = state.ry + drydt*dt;
	state.vy = state.vy + dvydt*dt;
	state.rz = state.rz + drzdt*dt;
	state.vz = state.vz + dvzdt*dt;

	return state;
}

State ee_integrate(State state, double t, double dt) {
	state.vx = state.vx + acceleration_x(state, t)*dt;
	state.vy = state.vy + acceleration_y(state, t)*dt;
	state.vz = state.vz + acceleration_z(state, t)*dt;

	state.rx = state.rx + state.vx*dt;
	state.ry = state.ry + state.vy*dt;
	state.rz = state.rz + state.vz*dt;

	return state;
}

double acceleration_x(State state, double t) {
	// \dot{v_x} = qB/m v_y + F_x/m
	return state.vy;
}
double acceleration_y(State state, double t) {
	// \dot{v_y} = -qB/m v_x + F_y/m
	return -state.vx;
}
double acceleration_z(State state, double t) {
	// \dot{v_z} = F_z/m
	return 0.0;
}

State EEuler(State state, double t0, double t1, double dt) {
	long i;
	long ntimesteps = floorl(((t1-t0)/dt)+0.5);

	for(i=0; i<ntimesteps; i++) {
		state = ee_integrate(state, t0, dt);
		t0 += dt;
	fprintf(stderr, "Ee %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f \n", t0+dt, state.rx, state.ry, state.rz, state.vx, state.vy, state.vz);
	}
	return state;
}

State RK4(State state, double t0, double t1, double dt) {
	long i;
	long ntimesteps = floorl(((t1-t0)/dt)+0.5);

	for(i=0; i<ntimesteps; i++) {
		state = rk_integrate(state, t0, dt);
		t0 += dt;
		fprintf(stderr, "Rr %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f \n", t0+dt, state.rx, state.ry, state.rz, state.vx, state.vy, state.vz);
	}
	return state;
}

State initial(void) {
	State state;
	state.rx = 0.0;
	state.ry = 0.0;
	state.rz = 0.0;
	state.vx = 1.0;
	state.vy = 0.0;
	state.vz = 1.0;

	return state;
}

int main(void) {
	double t0, t1, dt;
	State rkstate, eestate;
	int i;
	long ntimesteps;

	t0 = 0.0;
	t1 = 1.0;

	for(i = 1; i<10; i++) {
		ntimesteps = pow(10, i-1);
		dt = (t1-t0)/ntimesteps;
		fprintf(stderr, "dt=%1.10f\n",dt);
		rkstate = initial();
		rkstate = RK4(rkstate, t0, t1, dt);
		fprintf(stdout, "R %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %1.10f\n", t1, rkstate.rx, rkstate.ry, rkstate.rz, rkstate.vx, rkstate.vy, rkstate.vz, dt);

		eestate = initial();
		eestate = EEuler(eestate, t0, t1, dt);
		fprintf(stdout, "E %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %2.4f %1.10f\n", t1, eestate.rx, eestate.ry, eestate.rz, eestate.vx, eestate.vy, eestate.vz, dt);

	}
		fprintf(stdout, "   t1     rx     ry     rz     vx     vy     vz      dt\n");

	
