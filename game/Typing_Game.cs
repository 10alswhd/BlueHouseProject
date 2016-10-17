using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TypingGame
{
    public class ConsoleView
    {
        public void Menu() //will need to change this to retrieve difficulty for future releases.
        {
            Console.WriteLine("|========================|");
            Console.WriteLine("|     HERP DERP TYPO     |");
            Console.WriteLine("|========================|");
            Console.WriteLine("|  Enter your option     |");
            Console.WriteLine("|                        |");
            Console.WriteLine("|  1. NEW GAME           |");
            Console.WriteLine("|  2. HIGHSCORE          |");
            Console.WriteLine("|  3. DIFFICULITY        |");
            Console.WriteLine("|                        |");
            Console.WriteLine("|========================|");
            Console.ReadLine();
        }

        public void Countdown()
        {
            
            int countdown = 3;
            Console.WriteLine("{0}...", countdown);
            System.Threading.Thread.Sleep(1000);
            countdown--;
            Console.WriteLine("{0}...", countdown);
            System.Threading.Thread.Sleep(1000);
            countdown--;
            Console.WriteLine("{0}...", countdown);
            System.Threading.Thread.Sleep(1000);
              
        }

        public void PrintSentence(int question, string sentence)
        {
            Console.WriteLine(question + ". ");
            Console.WriteLine(sentence);
            //GET THE USERS SENTENCE INPUT?
        }

        public void timesUp()
        {
            Console.WriteLine("TIMES UP!");
            System.Threading.Thread.Sleep(1000);
        }

        public void PrintScore(int score, int mistakes)
        {
            Console.WriteLine("You made {0} mistakes", mistakes);
            Console.WriteLine("You scored" + score);
            //sleep for 500ms??
        }

        public string EnterName()
        {
            Console.WriteLine("New highscore!");
            Console.WriteLine("Enter your name...");
            string name = Console.ReadLine();
            return name;
        }

        public void HighscoresTable(Dictionary<string, int> highscoretable) //will need to change this to retrieve difficulty for future releases.
        {/*
            Console.WriteLine("|======================================|");
            Console.WriteLine("|  High Scores                         |");
            Console.WriteLine("|======================================|");
            Console.WriteLine("|  1. " + highscoretable[0] + "        |");
            Console.WriteLine("|  2. " + highscoretable[1] + "        |");
            Console.WriteLine("|  3. " + highscoretable[2] + "        |");
            Console.WriteLine("|  4. " + highscoretable[3] + "        |");
            Console.WriteLine("|  5. " + highscoretable[4] + "        |");
            Console.WriteLine("|  6. " + highscoretable[5] + "        |");
            Console.WriteLine("|  7. " + highscoretable[6] + "        |");
            Console.WriteLine("|  8. " + highscoretable[7] + "        |");
            Console.WriteLine("|  9. " + highscoretable[8] + "        |");
            Console.WriteLine("| 10. " + highscoretable[9] + "        |");
            Console.WriteLine("|======================================|"); */
        }
    }
}


 GameController.cs
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;

namespace TypingGame
{
    public class GameController
    {
        ConsoleView _view;
        Sentence _sentence;
        SentenceDB _sentencedb;
        public string[] SentenceToWords { get; set; }
        public string[] SentenceToWordsCompare { get; set; }
        public string StringDB { get; set; }
        public string Input { get; set; }

        public GameController()
        {
            _view = new ConsoleView();
            _sentence = new Sentence();
            _sentencedb = new SentenceDB();
        }

        public void StartGame()
        {
            _view.Menu();
            string menuSelect = Console.ReadLine();
            switch (menuSelect)
            {
                case "1":
                    _view.Countdown();
                    string sent = _sentencedb.GetSentence(2).SentenceString;
                    _view.PrintSentence(1,sent);
                    string sentence = Console.ReadLine();
                    string[] sentenceArray = sentence.Split(' ');
                    int mistakes = Mistakes(sentenceArray, sent);
                    Console.WriteLine(mistakes);
                    /*
                    _view.timesUp();
                    _view.PrintScore();
                    _view.EnterName();
                    _view.HighscoresTable();
                     * */
                    break;
                    
            }
        }

        public TimeSpan StartTimer()
        {
            var now = DateTime.Now.TimeOfDay;
            return now;
        }

        public TimeSpan EndTimer()
        {
            var end = DateTime.Now.TimeOfDay;
            return end;
        }

        public string CheckScore()
        {
            var nowSec = StartTimer().TotalSeconds;
            var endSec = EndTimer().TotalSeconds;
            var finalSec = endSec - nowSec;
            var nowMilli = StartTimer().TotalSeconds;
            var endMilli = EndTimer().TotalSeconds;
            var finalMilli = endMilli - nowMilli;
            return finalSec + ":" + finalMilli;
        }

        public int Mistakes(string[] sentenceArrayInput, string stringInput)
        {
            string[] inputArray = stringInput.Split(' ');
            int countMistakes = 0;

            for (int i = 0; i < sentenceArrayInput.Length; i++)
                {
                    if (sentenceArrayInput[i] != inputArray[i])
                    {
                        countMistakes++;
                    }
                }

            return countMistakes;
        }

                
    }
}



 Program.cs
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;

namespace TypingGame
{
    class Program
    {
        static void Main(string[] args)
        {
            GameController controller = new GameController();
            controller.StartGame();



            Console.WriteLine("Welcome to The Typing Game. Press enter to start. ");
            Console.Write("Please Enter your name: ");
            var username = Console.ReadLine();
            string sentence1 = "The quick brown fox jumped over the lazy dog?";

            //print out output
            Console.WriteLine(sentence1);
            var now = DateTime.Now.TimeOfDay;
            //input
            var sentence = Console.ReadLine();
            var end = DateTime.Now.TimeOfDay;
            Console.WriteLine("--------------------------------------------------------------------");
     
            var elasped = end - now;
            var currentTime = elasped.Seconds + ":" + elasped.Milliseconds;

            var countMistakes = 0;

            var sentenceToWords = sentence1.Split();
            var sentenceToWords1 = sentence.Split();


            if (sentenceToWords.Length == sentenceToWords1.Length)
            {
                for (int i = 0; i < sentenceToWords.Length; i++)
                {
                    if (sentenceToWords[i] != sentenceToWords1[i])
                    {
                        countMistakes++;
                    }
                }
            }

            


            if(sentence.Length == sentence1.Length)
            {
                if (sentence.Equals(sentence1) == false)
                {
                    Console.WriteLine("Sorry {0}, you have made {1} mistake.", username, countMistakes);
                    Console.WriteLine("Your current time: " + currentTime);
                    Console.ReadLine();
                }
                else Console.WriteLine("Well done {0}! You made zero mistakes.", username);
                Console.WriteLine("Your current time: " + currentTime);
                Console.ReadLine();
            }

            Console.WriteLine("Sorry {0}, Please try again. Input was invalid", username);
            Console.WriteLine("Your current time: " + currentTime);
            Console.ReadLine();

        }
    }
}



 Sentence.cs
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TypingGame
{
    public class Sentence
    {
        public string SentenceString { get; set; }
        public int SentenceLength { get; set; }
        public int Difficulty { get; set; }

        public Sentence()
        {

        }

    }
}




 SentenceDB.cs
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SqlClient;

namespace TypingGame
{
    public class SentenceDB
    {
        SqlConnection connection = new SqlConnection(@"Server=.\sqlexpress;Database=TypingGame;Trusted_Connection=True;");

        public Sentence GetSentence(int difficulty)
        {
            connection.Open();
            SqlCommand command = new SqlCommand("SELECT * FROM Lines WHERE difficulty = @difficulty");
            command.Parameters.AddWithValue("@difficulty", difficulty);
            Sentence sentence = new Sentence();

            using (SqlDataReader reader = command.ExecuteReader())
            {
                reader.Read();
                sentence.SentenceString = reader.GetString(reader.GetOrdinal("sentence_string"));
                sentence.SentenceLength = reader.GetInt32(reader.GetOrdinal("sentence_length"));
            }

            connection.Close();

            sentence.Difficulty = difficulty;
            return sentence;
        }
    }
}
