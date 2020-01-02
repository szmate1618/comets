using System.IO;
using System.Net;
using UnityEngine;
using UnityEngine.UI;


public class FetchNews : MonoBehaviour
{

	private string ParseNews(string rawText)
	{
		return rawText;
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
