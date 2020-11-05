using System;
using System.IO;
using System.Linq;
using System.Collections.Generic;

// This is obviously a manimalistic versiob of a Cellular Automaton but atleasg it worksssss

public static class CMath
{
	public static long Mod(long a, long n) { long result = a % n; if ((result<0 && n>0) || (result>0 && n<0)) { result += n; } return result; } // This is copied from the internet, thats why it looks like this.
	public static bool IsInRange(long num, long start, long end) {return num >= start && num < end;} // This one isnt copied tho
}

namespace GameOfLife
{
	public class Circle2DArray<value_type>
	{
		private value_type[,] array;
		public value_type this[long x, long y]
		{
			get
			{
				//Console.WriteLine($"{y} % {height} = {y % height}");
				return array[CMath.Mod(y, height), CMath.Mod(x, width)];
			}	
			set
			{
				array[CMath.Mod(y, height), CMath.Mod(x, width)] = value;
			}
		}
		public long width
		{
			get
			{
				return (long)array.GetLength(1);
			}
		}
		public long height
		{
			get
			{
				return (long)array.GetLength(0);
			}
		}
		public Circle2DArray(long width, long height)
		{
			array = new value_type[height, width];
		}
		public Circle2DArray(long width, long height, value_type fill)
		{
			array = new value_type[height, width];
			for (long y = 0; y < height; ++y)
				for (long x = 0; x < width; ++x)
					array[y, x] = fill;
		}
		public void Resize(long width, long height, value_type newfill)
		{
			value_type[,] new_array = new value_type[height, width];
			long copied_width = Math.Min(this.width, width);
			long copied_height = Math.Min(this.height, height);
			for (long y = 0; y < copied_height; ++y)
				for (long x = 0; x < copied_width; ++x)
					new_array[y, x] = array[y, x];

			for (; copied_width < width; ++copied_width)
				for (long y = 0; y < height; ++y)
					new_array[y, copied_width] = newfill;

			for (; copied_height < height; ++copied_height)
				for (long x = 0; x < width; ++x)
					new_array[copied_height, x] = newfill;
			array = new_array;
			// Console.WriteLine($"Resized stuff = ({refilled_width}, {refilled_height})");
		}
		public void CopyRefToThis(Circle2DArray<value_type> other)
		{
			array = other.array;
		}
	}
	public class ConwaysGOL : Circle2DArray<bool>
	{
		public int SurviveRules;
		public int BornRules;
		public bool Wrap;
		public static class Rules
		{
			public enum PreDefSurviveRules
			{
				Amoeba = (int)(BlocksNeeded.One | BlocksNeeded.Three | BlocksNeeded.Five | BlocksNeeded.Eight),
				Assimilation = (int)(BlocksNeeded.Four | BlocksNeeded.Five | BlocksNeeded.Six | BlocksNeeded.Seven),
				Coagulations = (int)(BlocksNeeded.Two | BlocksNeeded.Three | BlocksNeeded.Five | BlocksNeeded.Six | BlocksNeeded.Seven | BlocksNeeded.Eight),
				ConwaysLife = (int)(BlocksNeeded.Two | BlocksNeeded.Three),
				Coral = (int)(BlocksNeeded.Four | BlocksNeeded.Five | BlocksNeeded.Six | BlocksNeeded.Seven | BlocksNeeded.Eight),
				DayAndNight = (int)(BlocksNeeded.Three | BlocksNeeded.Four | BlocksNeeded.Six | BlocksNeeded.Seven | BlocksNeeded.Eight),
				Diamoeba = (int)(BlocksNeeded.Five | BlocksNeeded.Six | BlocksNeeded.Seven | BlocksNeeded.Eight),
				Flakes = (int)(BlocksNeeded.Zero | BlocksNeeded.One | BlocksNeeded.Two | BlocksNeeded.Five | BlocksNeeded.Six | BlocksNeeded.Seven | BlocksNeeded.Eight),
				Gnarl = (int)(BlocksNeeded.One),
				HighLife = (int)(BlocksNeeded.Two | BlocksNeeded.Three),
				InverseLife = (int)(BlocksNeeded.Three | BlocksNeeded.Four | BlocksNeeded.Six | BlocksNeeded.Seven | BlocksNeeded.Eight),
				LongLife = (int)(BlocksNeeded.Five),
				Maze = (int)(BlocksNeeded.One | BlocksNeeded.Two | BlocksNeeded.Three | BlocksNeeded.Four | BlocksNeeded.Five),
				Mazectric = (int)(BlocksNeeded.One | BlocksNeeded.Two | BlocksNeeded.Three | BlocksNeeded.Four),
				Move = (int)(BlocksNeeded.Two | BlocksNeeded.Four | BlocksNeeded.Five),
				PseudoLife = (int)(BlocksNeeded.Two | BlocksNeeded.Three | BlocksNeeded.Eight),
				Replicator = (int)(BlocksNeeded.One | BlocksNeeded.Three | BlocksNeeded.Five | BlocksNeeded.Seven),
				Seeds = 0,
				Serviettes = 0,
				Stains = (int)(BlocksNeeded.Two | BlocksNeeded.Three | BlocksNeeded.Five | BlocksNeeded.Six | BlocksNeeded.Seven | BlocksNeeded.Eight),
				WalledCities = (int)(BlocksNeeded.Two | BlocksNeeded.Three | BlocksNeeded.Four | BlocksNeeded.Five)
			}
			public enum PreDefBornRules
			{
				Amoeba = (int)(BlocksNeeded.Three | BlocksNeeded.Five | BlocksNeeded.Seven),
				Assimilation = (int)(BlocksNeeded.Three | BlocksNeeded.Four | BlocksNeeded.Five),
				Coagulations = (int)(BlocksNeeded.Three | BlocksNeeded.Seven | BlocksNeeded.Eight),
				ConwaysLife = (int)(BlocksNeeded.Three),
				Coral = (int)(BlocksNeeded.Three),
				DayAndNight = (int)(BlocksNeeded.Three | BlocksNeeded.Six | BlocksNeeded.Seven | BlocksNeeded.Eight),
				Diamoeba = (int)(BlocksNeeded.Three | BlocksNeeded.Five | BlocksNeeded.Six | BlocksNeeded.Seven | BlocksNeeded.Eight),
				Flakes = (int)(BlocksNeeded.Three),
				Gnarl = (int)(BlocksNeeded.One),
				HighLife = (int)(BlocksNeeded.Three | BlocksNeeded.Six),
				InverseLife = (int)(BlocksNeeded.Zero | BlocksNeeded.One | BlocksNeeded.Two | BlocksNeeded.Three | BlocksNeeded.Four | BlocksNeeded.Seven | BlocksNeeded.Eight),
				LongLife = (int)(BlocksNeeded.Three | BlocksNeeded.Four | BlocksNeeded.Five),
				Maze = (int)(BlocksNeeded.Three),
				Mazectric = (int)(BlocksNeeded.Three),
				Move = (int)(BlocksNeeded.Three | BlocksNeeded.Six | BlocksNeeded.Eight),
				PseudoLife = (int)(BlocksNeeded.Three | BlocksNeeded.Five | BlocksNeeded.Seven),
				Replicator = (int)(BlocksNeeded.One | BlocksNeeded.Three | BlocksNeeded.Five | BlocksNeeded.Seven),
				Seeds = (int)(BlocksNeeded.Two),
				Serviettes = (int)(BlocksNeeded.Two | BlocksNeeded.Three | BlocksNeeded.Four),
				Stains = (int)(BlocksNeeded.Three | BlocksNeeded.Six | BlocksNeeded.Seven | BlocksNeeded.Eight),
				WalledCities = (int)(BlocksNeeded.Four | BlocksNeeded.Five | BlocksNeeded.Six | BlocksNeeded.Seven | BlocksNeeded.Eight)
			}
			public enum BlocksNeeded
			{
				Zero = 1,
				One = 2,
				Two = 4,
				Three = 8,
				Four = 16,
				Five = 32,
				Six = 64,
				Seven = 128,
				Eight = 256,
				Nine = 512
			}
			public static bool IntContains(int num, BlocksNeeded rule)
			{
				return (num & (int)rule) != 0;
			}
			public static int AddToInt(int num, BlocksNeeded rule)
			{
				return num | (int)rule;
			}
			public static int RemoveFromInt(int num, BlocksNeeded rule)
			{
				return num & ~(int)rule;
			}
			public static BlocksNeeded IntToBlocksNeeded(int num)
			{
				switch (num)
				{
				case 0:
					return BlocksNeeded.Zero;
				case 1:
					return BlocksNeeded.One;
				case 2:
					return BlocksNeeded.Two;
				case 3:
					return BlocksNeeded.Three;
				case 4:
					return BlocksNeeded.Four;
				case 5:
					return BlocksNeeded.Five;
				case 6:
					return BlocksNeeded.Six;
				case 7:
					return BlocksNeeded.Seven;
				case 8:
					return BlocksNeeded.Eight;
				default:
					throw new ArgumentException($"Invalid blocks needed amount, {num}");
				}
			}
		}
		public ConwaysGOL(long width, long height) : base(width, height, false)
		{
			SurviveRules = (int)Rules.PreDefSurviveRules.ConwaysLife;
			BornRules = (int)Rules.PreDefBornRules.ConwaysLife;
		}
		public void NextGenAt(long x, long y)
		{
			this[x, y] = DetermineNextState(x, y);
		}
		private bool DetermineNextState(long x, long y)
		{
			int count = GetTrueCountAt(x, y);
			//Console.WriteLine($"({x}, {y}) = {GetAt(x, y)} {this[x, y]}");
			if (count == 0) return false;
			if (GetAt(x, y))
				return (SurviveRules & (1 << (count - 1))) != 0;
			//Console.WriteLine($"S = {SurviveRules} B = {BornRules}");
			return (BornRules & (1 << count)) != 0;
		}
		private int GetTrueCountAt(long x, long y)
		{
			int count = 0;
			for (long X = -1; X < 2; ++X)
				for (long Y = -1; Y < 2; ++Y)
					if (GetAt(x+X, y+Y))
						++count;
			//Console.WriteLine($"Count is {count}");
			return count;
		}
		public Circle2DArray<bool> GetNextGeneration()
		{
			Circle2DArray<bool> nextgen = new Circle2DArray<bool>(width, height);
			//Console.WriteLine(nextgen);
			for (long x = 0; x < width; ++x)
				for (long y = 0; y < height; ++y)
					nextgen[x, y] = DetermineNextState(x, y);
			return nextgen;
		}
		public void NextGeneration()
		{
			this.CopyRefToThis(GetNextGeneration());
		}
		public void FastPrint()
		{
			string printed = "";
			for (long y = 0; y < height; ++y)
			{
				for (long x = 0; x < width; ++x)
					printed += (this[x, y] ? '⬜' : '⬛');
				printed += '\n';
			}
			Console.WriteLine(printed);
		}
		public bool GetAt(long x, long y)
		{
			if (Wrap || (CMath.IsInRange(x, 0, width) && CMath.IsInRange(y, 0, height)))
				return this[x, y];
			return false;
		}
		public void SetAt(long x, long y, bool val)
		{
			if (Wrap || (CMath.IsInRange(x, 0, width) && CMath.IsInRange(y, 0, height)))
				this[x, y] = val;
		}
	}
}

namespace MainNS
{
	using GameOfLife;
	using System.Threading;
    public static class Program 
    {
        public static void Main() 
        {
    		ConwaysGOL gol = new ConwaysGOL(10, 10);
    		gol.Wrap = true;
    		gol.SurviveRules = (int)ConwaysGOL.Rules.PreDefSurviveRules.ConwaysLife;
    		gol.BornRules = (int)(1 | 2 | 16 | 32 | 64 | 128 | 256);
    		gol.BornRules = (int)ConwaysGOL.Rules.PreDefBornRules.ConwaysLife;
    		//gol.Print();
    		//Console.WriteLine("Hey");
    		gol.Resize(15, 21, false);
    		//gol[7, 10] = true;
    		gol[1, 0] = true;
    		gol[0, 1] = true;
    		gol[0, 2] = true;
    		gol[1, 2] = true;
    		gol[2, 2] = true;
    		while (true)
    		{
    			Thread.Sleep(1000);
    			Console.Clear();
    			gol.FastPrint();
    			//Console.WriteLine("====================================");
    			gol.NextGeneration();
    		}
    		/*
    		gol.Wrap = true;
    		gol[1, 0] = true;
    		gol[0, 1] = true;
    		gol[0, 2] = true;
    		gol[1, 2] = true;
    		gol[2, 2] = true;
    		while (true)
    		{
    			gol.Print();
    			Console.WriteLine("----------");
    			//Console.ReadLine();
    			//Console.WriteLine("----------");
    			gol.NextGeneration();
    		}*/
        }
    }
}
