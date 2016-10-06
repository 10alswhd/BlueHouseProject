package testapps.sound.midi;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import javax.sound.midi.MidiChannel;
import javax.sound.midi.MidiSystem;
import javax.sound.midi.MidiUnavailableException;
import javax.sound.midi.Synthesizer;

/** 
* @author ypetya@gmail.com
*/
public class MidiFractal{

	//C, D, E, G, A, C
//	private final int [] pentatone = {60, 62, 64, 67, 69, 72};
		
	private enum Operation {
		PAUSE(0,0),
		C_4(1,60),
		D_4(2,62),
		E_4(3,64),
		G_4(4,67),
		A_4(5,69),
		C_5(6,72),
		
		// comment these, if you need pentatone only
		X_40(9,60),
		X_41(10,62),
		X_42(11,64),
		X_43(12,67),
		X_44(13,69),
		X_45(14,72),
		
		CHANGE_TEMPO(7,0),
		FORTE(8,0);
		int val;
		int tone;
		Operation(int i, int tone) {
			this.val = i;
			this.tone = tone;
		}
		static Operation from(int i) {
			return values()[(i+1) % values().length];
		}
		public int getVal() {
			return val;
		}
		public int getTone() {
			return tone;
		}		
	}
	
	private final MidiChannel [] channels;
	
	private List<Integer> track;
	
	
	private MidiFractal(Synthesizer synth) {
		channels = synth.getChannels();
		System.out.println("There are " + channels.length + " channels.");
	}	
	
	private static int velocity = 93;
	private static int delay = 148;
	private static int ruleMaxDifficulity = 3;
	private static int recursionDepth = 2;

	boolean tempo_speedup = false;
	boolean forte = false;
	int fortecounter = 0;
	int tempocounter = 0;
	int toneCounter = 0;
	private void play() {
		for(int i=0;i < track.size()-1; i+=2) {
			Operation operation = Operation.from(track.get(i+1));
			switch(operation) {
			default:
			case C_4 :
			case D_4 :
			case E_4 :
			case G_4 :
			case A_4 :
			case C_5 :
				int ch = (i+1)%channels.length;
				System.out.print( "" + ch + ":" + operation.name() + " ");
				if(toneCounter++ % 20 == 0) {
					System.out.println();
				}
				// FIXME nem hasznaljuk ki minden channelt, csak amennyi Operationunk van
				channels[ch].noteOn(operation.getTone(), velocity);
				suspend( delay );
				break;
			case CHANGE_TEMPO :
				if(tempocounter++ < 10) {
					break;
				}
				if(tempo_speedup) {
					tempo_speedup = false;
					delay = delay / 2;
					System.out.println("\ntempo up!");
					tempocounter = 4;
				} else {
					tempo_speedup = true;
					delay = delay * 2;
					System.out.println("\ntempo down!");
					tempocounter = 0;
				}					
				break;
			case FORTE:
				if(fortecounter++<5) {
					break;
				}
				if(forte) {
					forte = false;
					System.out.print("forte! ");
					velocity = 115;
					fortecounter = 3;
				} else  {
					forte = true;
					System.out.print("forte off! ");
					velocity = 74;
					fortecounter = 0;
				}
				break;
			case PAUSE :
				System.out.print("pause ");
				suspend( delay );				
				break;
			}
		}
	}

	private static void suspend(int msec) {
		try {
			Thread.sleep(msec);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	private static List<Integer> generateRule(Random rand, int numOfCols) {
		int cols = rand.nextInt(numOfCols-1)+2;
		List<Integer> rule = new ArrayList<Integer>(cols);
		for(int j=0;j<cols;j++) {
			rule.add( rand.nextInt( Operation.values().length ) );
		}
		return rule;
	}
	
	private static List<List<Integer>> generateFractalRules(Random rand, int numOfRows, int numOfCols) {
		List<List<Integer>> rules = new ArrayList<List<Integer>>();
		// safety 1
		for(int i=0;i<numOfRows+1;i++) {
			rules.add(generateRule(rand, numOfCols));
		}
		return rules;
	}
	
	private static List<Integer> generateRecursive(List<Integer> program, List<List<Integer>> rules, int depth) {
		if(depth == 0) return program;
		List<Integer> ret = new ArrayList<Integer>();
		for(Integer i:program) {
			// itt modulo-sra tenni
			List<Integer> in = rules.get( (i+1) % rules.size());
			ret.addAll(in);
		}
		return generateRecursive( ret, rules, depth-1 );
	}
	
	/**
	 * @param args
	 * @throws MidiUnavailableException 
	 */
	public static void main(String[] args) throws MidiUnavailableException {
		Synthesizer synth = MidiSystem.getSynthesizer();
		synth.open();
		// random solo :)
		//MidiFractal mf = new MidiFractal(synth,1);

		Random rand = new Random(System.currentTimeMillis());
	
		// fractal rules
		List<List<Integer>> rules = generateFractalRules(rand, 3, ruleMaxDifficulity);
	
		List<Integer> program = new ArrayList<Integer>();
		program.add(0);
		program.add(1);
		program = generateRecursive(program, rules, recursionDepth);
		
		MidiFractal mf = new MidiFractal(synth);
		
		for(;;) {			
//			System.out.println("\nrules : " + rules);
//			System.out.println("The program : " + program);
			
			mf.setTrack(program);
			
			mf.play();
			
			program = changeProgram(rand, rules, program, Operation.values().length, ruleMaxDifficulity);
		}
	}

	private static List<Integer> changeProgram(Random rand, List<List<Integer>> rules, List<Integer> program, int numOfRules, int numOfCols) {
		List<Integer> newRule = generateRule(rand, numOfCols);
		rules.set(rand.nextInt(rules.size()), newRule);
		program = generateRecursive(program, rules, 2);
		program = program.subList(0, Math.min(100,program.size()));
		return program;
	}

	public void setTrack(List<Integer> track) {
		this.track = track;
	}

}
