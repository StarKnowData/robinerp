using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using BCST.Cache;
using BCST.Common;

public partial class Public_Thumbs : System.Web.UI.Page
{
	/// <summary>
	/// 要转换的图片路径，应为编码过的绝对路径，如：/Images/1.jpg
	/// </summary>
	protected string FilePath
	{
		get
		{
			return CommonManager.Web.RequestUrlDecode( "path", "" );
		}
	}
	/// <summary>
	/// 要输出的图片宽度
	/// </summary>
	protected int Width
	{
		get
		{
			string tmp = CommonManager.Web.Request( "width", "150" );
			if( CommonManager.String.IsInteger( tmp ) )
				return int.Parse( tmp );
			else
				return 150;
		}
	}
	/// <summary>
	/// 要输出的图片高度
	/// </summary>
	protected int Height
	{
		get
		{
			string tmp = CommonManager.Web.Request( "height", "150" );
			if( CommonManager.String.IsInteger( tmp ) )
				return int.Parse( tmp );
			else
				return 150;
		}
	}

	protected void Page_Load( object sender, EventArgs e )
	{
		byte[] s = null;
		if( BCSTCache.Default.Get<AspNetCache>( this.FilePath + this.Width + this.Height ) == null )
		{
			s = CommonManager.File.GraphicsImages( this.FilePath, this.Width, this.Height );
			if( s != null && s.Length > 0 )
				BCSTCache.Default.Save<AspNetCache>( this.FilePath + this.Width + this.Height, s, 1 );
		}
		else
		{
			s = (byte[])BCSTCache.Default.Get<AspNetCache>( this.FilePath + this.Width + this.Height );
		}
		if( s == null || s.Length <= 0 )
		{
			return;
		}
		string profix = this.FilePath.Substring( this.FilePath.LastIndexOf( '.' ) + 1 );
		Response.Clear();
		Response.ContentType = CommonManager.File.GetFileContentType( profix );
		Response.BinaryWrite( s );
		Response.End();
	}
}
