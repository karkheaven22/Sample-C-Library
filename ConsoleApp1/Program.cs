// See https://aka.ms/new-console-template for more information
using InteropLib;
using System.Reflection.Emit;

Console.WriteLine("Hello, World!");
CallManagedClass();

static void CallManagedClass()
{
    
    Console.WriteLine($"=== Managed class ===");
    var prop = new PropertyWrapper();
    prop.Amount = 100000;
    prop.AddPayment(new ManagedPayment(new DateTime(2025, 10, 1), 1000));
    prop.AddInterest(new ManagedInterest(new DateTime(2025, 1, 1), 3));

    ManagedDailyCompound result = prop.GetMonthlyInterest(1, 2025);
    // 打印结果
    Console.WriteLine($"Date: {result.IDate.ToDateTime()}");
    Console.WriteLine($"Balance: {result.Balance}");
    Console.WriteLine($"Rate: {result.Rate}");
    Console.WriteLine($"Pay: {result.Pay}");
    Console.WriteLine($"Rate_Amount: {result.InterestAmount}");
    //var a = new Property.interop();
    //double result = a.EqualAmortization(100000, 3.4, 360);

    //Console.WriteLine(result);
}