using System.IO;
using System.Net;
using UnityEngine;
using UnityEngine.UI;


public class FetchNews : MonoBehaviour
{

	private string ParseNews(string rawText)
	{
		//TODO: This is good enough for now, but in the real system, news should
		//have a fixed, specific format, e.g. JSON, or just plain text without any markup,
		//so we don't need to change this function every time
		//we make a small change on the news page of the website.
		return rawText.Replace("<h1>", "").Replace("</h1>", "");
	}

	public void Start ()
	{
		string html;
		string newsUrl = @"https://szmate1618.github.io/comets-website/news/recent.html";

		HttpWebRequest request = (HttpWebRequest)WebRequest.Create(newsUrl);

		using (HttpWebResponse response = (HttpWebResponse)request.GetResponse())
		using (Stream stream = response.GetResponseStream())
		using (StreamReader reader = new StreamReader(stream))
		{
			html = reader.ReadToEnd();
		}

		GetComponent<Text>().text = ParseNews(html);
	}

}
