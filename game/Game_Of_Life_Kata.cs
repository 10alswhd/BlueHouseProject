using System.Collections.Generic;
using System.Linq;
using NSpec;

namespace GameOfLifeKata
{
    class describe_Cell_Tick : nspec
    {
        void before_each()
        {
            cell = new Cell();
        }

        void act_each()
        {
            cell.Tick();
        }

        void a_dead_cell()
        {
            before = () => cell.Alive = false;

            context["after a tick"] = () =>
            {
                specify = () => cell.IsDead().is_true();

                context["given 2 live neighbors"] = () =>
                {
                    before = () => cell.AdjacentCells = LiveCells(2);

                    specify = () => cell.IsAlive().is_false();
                };

                context["given exactly 3 live neighbors"] = () =>
                {
                    before = () => cell.AdjacentCells = LiveCells(3);

                    specify = () => cell.IsAlive().is_true();
                };

                context["given 4 live neighbors"] = () =>
                {
                    before = () => cell.AdjacentCells = LiveCells(4);

                    specify = () => cell.IsAlive().is_false();
                };
            };
        }

        void a_live_cell()
        {
            before = () => cell.Alive = true;

            specify = () => cell.IsDead().is_true();

            context["given exactly 1 live neighbors"] = () =>
            {
                before = () => cell.AdjacentCells = LiveCells(1);

                specify = () => cell.IsDead().is_true();
            };

            context["given exactly 2 live neighbors"] = () =>
            {
                before = () => cell.AdjacentCells = LiveCells(2);

                specify = () => cell.IsAlive().is_true();
            };

            context["given exactly 3 live neighbors"] = () =>
            {
                before = () => cell.AdjacentCells = LiveCells(3);

                specify = () => cell.IsAlive().is_true();
            };
            
            context["given exactly 4 live neighbors"] = () =>
            {
                before = () => cell.AdjacentCells = LiveCells(4);

                specify = () => cell.IsDead().is_true();
            };

            context["given 2 dead neighbors"] = () =>
            {
                before = () => cell.AdjacentCells = new List<Cell>{new Cell(false), new Cell(false)};

                specify = () => cell.IsDead().is_true();
            };

            context["given 2 dead neighbors and 2 live neighbors"] = () =>
            {
                before = () => cell.AdjacentCells = new List<Cell>
                                                    {
                                                        new Cell(false), new Cell(false),
                                                        new Cell(true), new Cell(true)
                                                    };

                specify = () => cell.IsAlive().is_true();
            };
        }

        private static IEnumerable<Cell> LiveCells(int quantity)
        {
            return Enumerable.Range(1, quantity).Select(i => new Cell(true));
        }

        private Cell cell;
    }
}

using System.Collections.Generic;
using System.Linq;

namespace GameOfLifeKata
{
    public class Cell
    {
        public IEnumerable<Cell> AdjacentCells { get; set; }

        public void Tick()
        {
            if (LiveNeighbors() == 3) Alive = true;

            if (Alive.Equals(true) && (LiveNeighbors() < 2 || LiveNeighbors() > 3)) Alive = false;
        }

        private int LiveNeighbors()
        {
            return AdjacentCells.Count(c => c.IsAlive());
        }

        public bool IsAlive()
        {
            return Alive;
        }

        public bool IsDead()
        {
            return !Alive;
        }

        public bool Alive { get; set; }

        public Cell() : this(false) { }

        public Cell(bool alive)
        {
            AdjacentCells = new List<Cell>();

            Alive = alive;
        }
    }
}
