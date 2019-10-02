using System;
using System.Collections.Specialized;
using System.Linq;
using System.Text;
using System.Globalization;
using System.IO;
using System.Net;
using System.Net.Sockets;

using MySql.Data;
using MySql.Data.MySqlClient;

namespace WeatherStationServer
{
    class Program
    {
        static void Main(string[] args)
        {
            string user = "*****";
            string password = "*****";
            string connStr = "server=databases.aii.avans.nl;user="+user+";database=jwigcher_db;port=3306;password="+password+";";
            MySqlConnection conn = new MySqlConnection(connStr);

            TcpListener server = new TcpListener(new IPEndPoint(IPAddress.Any, 8080));

            server.Start();

            while (true)
            {
                if (server.Pending())
                {
                    try
                    { 
                        Socket socket = server.AcceptSocket();

                        BinaryReader reader = new BinaryReader(new NetworkStream(socket));
                        float temp = reader.ReadSingle();
                        float humidity = reader.ReadSingle();

                        socket.Close();

                        string date = string.Format("{0}-{1:00}-{2:00}", DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);

                        conn.Open();

                        MySqlCommand command = conn.CreateCommand();

                        command.CommandText =
                            string.Format("INSERT INTO data (temperature, humidity, date, time) VALUES ({0}, {1}, '{2}', '{3}');",
                            temp.ToString(CultureInfo.InvariantCulture),
                            humidity.ToString(CultureInfo.InvariantCulture),
                            date, 
                            DateTime.Now.ToLongTimeString()
                            );

                        command.ExecuteNonQuery();
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine(ex.ToString());
                    }

                    try
                    {
                        conn.Close();
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine(ex.ToString());
                    }
                }
            }
        }
    }
}
