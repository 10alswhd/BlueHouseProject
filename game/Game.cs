using System;
using System.Collections.Generic;
using GameFramework;
using System.Drawing;
using OpenTK;
using OpenTheDoor;

namespace Collision {
    class Game {
        protected Point spawnTile = new Point(2, 1);
        protected PlayerCharacter hero = null;
        protected string heroSheet = "Assets/Link.png";
        public OpenTK.GameWindow Window = null;

        Map room1 = null;
        Map room2 = null;
        Map currentRoom = null;

        protected int[][] room1Layout = new int[][] {
            new int[] { 1, 1, 1, 1, 1, 1, 1, 1 },
            new int[] { 1, 0, 0, 0, 0, 0, 0, 1 },
            new int[] { 1, 0, 1, 0, 0, 0, 0, 1 },
            new int[] { 1, 0, 0, 0, 0, 1, 0, 1 },
            new int[] { 1, 0, 0, 0, 0, 0, 0, 2 },
            new int[] { 1, 1, 1, 1, 1, 1, 1, 1 }
        };

        protected int[][] room2Layout = new int[][] {
            new int[] { 1, 1, 1, 1, 1, 1, 1, 1 },
            new int[] { 2, 0, 0, 0, 1, 0, 0, 1 },
            new int[] { 1, 0, 0, 0, 0, 0, 0, 1 },
            new int[] { 1, 0, 0, 0, 0, 0, 0, 1 },
            new int[] { 1, 0, 0, 0, 1, 0, 0, 1 },
            new int[] { 1, 1, 1, 1, 1, 1, 1, 1 }
        };

        protected string spriteSheets = "Assets/HouseTiles.png";
        protected Rectangle[] spriteSources = new Rectangle[] {
            new Rectangle(466,32,30,30),
            new Rectangle(466,1,30,30),
            new Rectangle(32, 187, 30, 30),
            new Rectangle(32, 187, 30, 30)
        };
        
        public Tile GetTile(PointF pixelPoint) {
            return currentRoom[(int)pixelPoint.Y / 30][(int)pixelPoint.X / 30];
        }

        public Rectangle GetTileRect(PointF pixelPoint) {
            int xTile = (int)pixelPoint.X / 30;
            int yTile = (int)pixelPoint.Y / 30;
            Rectangle result = new Rectangle(xTile * 30, yTile * 30, 30, 30);
            return result;
        }

        //Singleton
        private static Game instance = null;
        public static Game Instance {
            get {
                if (instance == null) {
                    instance = new Game();
                }
                return instance;
            }
        }

        protected Game() {

        }

        public void Initialize(OpenTK.GameWindow window) {
            Window = window;
            window.ClientSize = new Size(room1Layout[0].Length * 30, room1Layout.Length * 30);
            TextureManager.Instance.UseNearestFiltering = true;

            hero = new PlayerCharacter(heroSheet, new Point(spawnTile.X * 30, spawnTile.Y * 30));
            room1 = new Map(room1Layout, spriteSheets, spriteSources, 0, 2); // 0 and 2 ae walkable
            room1[4][7].IsDoor = true;
            room2 = new Map(room2Layout, spriteSheets, spriteSources, 0, 2); // 0 and 2 are walkable
            room2[1][0].IsDoor = true;
            currentRoom = room1;
        }

        public void Update(float dt) {
            hero.Update(dt);

            // We need to check for doors AFTER the player has moved

            // Loop torugh the layout, the Tile class does not know if it is a door or not.
            for (int row = 0; row < currentRoom.Length; ++row) {
                for (int col = 0; col < currentRoom[row].Length; ++col) {
                    // The tile is a door if it had a 2 in the layout!
                    if (currentRoom[row][col].IsDoor) {
                        // Get the door's bounding rectangle
                        Rectangle doorRect = GetTileRect(new PointF(col * 30, row * 30));

                        // Get a small rectangle in the center of the player
                        Rectangle playerCenter = new Rectangle((int)hero.Center.X - 2, (int)hero.Center.Y - 2, 4, 4);

                        // Look for an intersection
                        Rectangle intersection = Intersection.Rect(doorRect, playerCenter);

                        // Intersection happens if the intersect rectangle has an area > 0
                        if (intersection.Width * intersection.Height > 0) {
                            // If we are in room1, move to room 2
                            if (currentRoom == room1) {
                                // Set active room
                                currentRoom = room2;

                                // Reposition hero to tile outside of door
                                hero.Position.X = 1 * 30; // Column 1
                                hero.Position.Y = 1 * 30; // Row 1
                            }
                            // If we are in room 2, move to room 1
                            else {
                                // Set active room
                                currentRoom = room1;

                                // Reposition hero to tile outside of door
                                hero.Position.X = 6 * 30; // Column 6
                                hero.Position.Y = 4 * 30; // Row 4
                            }
                        }
                    }
                }
            }
        }

        public void Render() {
            currentRoom.Render();
            hero.Render();
        }

        public void Shutdown() {
            room1.Destroy();
            room2.Destroy();
            hero.Destroy();
        }
    }
}
