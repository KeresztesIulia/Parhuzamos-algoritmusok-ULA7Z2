using System.Text;
using System.Diagnostics;

void Main()
{
    
    string readPath = "texts/plaintext.txt";
    TextReader readText = File.OpenText(readPath);
    string toCode = readText.ReadLine();
    string keyword = readText.ReadLine();

    if (toCode == null || keyword == null)
    {
        Console.WriteLine("ERROR: Nincs elegendő szöveg!");
        return;
    }
    readText.Close();
    int originalTextLength = toCode.Length;

    Stopwatch stopwatch = new Stopwatch();
    stopwatch.Start();
    Parallel.Invoke(
        () => Normalize(ref toCode),
        () => Normalize(ref keyword));

    CodeCsharp(ref toCode, keyword);
    double codeTime = stopwatch.Elapsed.TotalSeconds;

    WriteToFile(ref toCode, "texts/coded.txt");
    TimeToFile(originalTextLength, codeTime, "texts/time.txt");

    Console.WriteLine(codeTime + " End");

}
void Normalize(ref string text)
{
    RemoveNonAlpha(ref text);
    ToUpperParallel(ref text);
}

void RemoveNonAlpha(ref string text)
{
    StringBuilder text_sb = new StringBuilder();
    for (int i = 0; i < text.Length; i++)
    {
        if (Char.IsLetter(text[i]))
        {
            text_sb.Append(text[i]);
        }
    }
    text = text_sb.ToString();
}
void ToUpperParallel(ref string text)
{
    StringBuilder text_sb = new StringBuilder(text);
    ParallelLoopResult res = Parallel.For(0, text.Length, i =>
    {
        if (!Char.IsUpper(text_sb[i]))
        {
            text_sb[i] = Char.ToUpper(text_sb[i]);
        }
    });
    text = text_sb.ToString();
}

void CodeCsharp(ref string toCode, string keyword)
{
    StringBuilder toCode_sb = new StringBuilder(toCode);
    int kw_length = keyword.Length;
    Parallel.For(0, toCode.Length, i =>
    {
        int kw_index = i % kw_length;
        toCode_sb[i] = CodeLetter(toCode_sb[i], keyword[kw_index]);
    });
    toCode = toCode_sb.ToString();
}

char CodeLetter(char toCode, char key)
{
    toCode = (char)(toCode + key - 'A');
    if (toCode > 'Z')
    {
        toCode = (char)('A' + (toCode - 'Z') - 1);
    }
    return toCode;
}

void WriteToFile(ref string coded, string path)
{
    StreamWriter writer = new StreamWriter(path);
    writer.Write(coded);
    writer.Close();
}

void TimeToFile(int textLength, double codeTime, string path)
{
    StreamWriter writer = File.AppendText(path);
    writer.WriteLine(textLength + ":\t" + codeTime);
    writer.Close();
}

Main();