// See https://aka.ms/new-console-template for more information
Console.WriteLine("Hello, World!");
CallManagedClass();

static void CallManagedClass()
{
    Console.WriteLine($"=== Managed class ===");
    var a = new Property.interop();
    double result = a.EqualAmortization(100000, 3.4, 360);

    Console.WriteLine(result);
}