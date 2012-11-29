using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;
using BCST.Common;
using System.Xml;
using System.IO;


public partial class Admin_Lotter_LotterConfig : AdminBasePage
    {
    
        protected void Page_Load(object sender, EventArgs e)
        {
            AdminPopedom.IsHoldModel("18");
            if (!IsPostBack)
            {
                DataTable sd = DbSession.Default.FromSql("select top 1 * from Web_LotterConfig ").ToDataTable();

                if (sd.Rows.Count > 0)
                {
                    DataRow dr = sd.Rows[0];
                    txtGoldMoney.Text = dr["GoldMoney"].ToString();
                    txtSilverMoney.Text = dr["SilverMoney"].ToString();
                    txtJadeMoney.Text=dr["JadeMoney"].ToString();
                    txtBeginTime.Text = dr["BeginTime"].ToString();
                    txtEndTime.Text=dr["EndTime"].ToString();
                    hidType.Value = "1";
                   
                }
                sd.Clear();
            }
        }

        protected void Edit(object sender, EventArgs e)
        {
            string strGoldMoney = txtGoldMoney.Text.Trim();
            string strSilverMoney = txtSilverMoney.Text.Trim();
            string strJadeMoney = txtJadeMoney.Text.Trim();
            string beginTime = txtBeginTime.Text;
            string endTime = txtEndTime.Text;
            if (!CommonManager.String.IsInteger(strGoldMoney) || Convert.ToInt32(strGoldMoney) < 0)
            {
                CommonManager.Web.RegJs(this.Page, "alert('金奖所需的金币数请输入大于或等于0的整数！');", true);
                return;
            }
            if (!CommonManager.String.IsInteger(strSilverMoney) || Convert.ToInt32(strSilverMoney) < 0)
            {
                CommonManager.Web.RegJs(this.Page, "alert('银奖所需的金币数请输入大于或等于0的整数！');", true);
                return;
            }
            if (!CommonManager.String.IsInteger(strJadeMoney) || Convert.ToInt32(strJadeMoney) < 0)
            {
                CommonManager.Web.RegJs(this.Page, "alert('玉奖所需的金币数请输入大于或等于0的整数！');", true);
                return;
            }
             
            if (hidType.Value=="1")
            {
                DbSession.Default.FromSql("update Web_LotterConfig set GoldMoney=" + strGoldMoney + " ,SilverMoney=" + strSilverMoney + " ,JadeMoney=" + strJadeMoney+",BeginTime='"+beginTime+"' ,EndTime='"+endTime+"'").Execute();
            }
            else
            {
                DbSession.Default.FromSql(" insert into Web_LotterConfig values("+strGoldMoney+","+strSilverMoney+","+strJadeMoney+",'"+beginTime+"','"+endTime+"') ").Execute();
            }
             string xmlPath = Server.MapPath("/Upload/xml/LotterConfig.xml");
                XmlDocument xml = new XmlDocument();

                if (!File.Exists(xmlPath))
                {
                    //如果不存在就创建该文件

                    xml.LoadXml("<?xml version=\"1.0\" encoding=\"utf-8\"?><bcaster></bcaster>");//创建xml文件头部
                    XmlElement xmlRoot = xml.DocumentElement;//获取根元素
                    XmlElement xmlSon = xml.CreateElement("item");
                    XmlAttribute xmlattr = xml.CreateAttribute("id");
                    xmlattr.Value = "1";
                    xmlSon.Attributes.Append(xmlattr);

                    XmlElement gold = xml.CreateElement("Gold");
                    gold.InnerText = strGoldMoney;
                    xmlSon.AppendChild(gold);

                    XmlElement silver = xml.CreateElement("Silver");
                    silver.InnerText = strSilverMoney;
                    xmlSon.AppendChild(silver);

                    XmlElement jade = xml.CreateElement("Jade");
                    jade.InnerText = strJadeMoney;
                    xmlSon.AppendChild(jade);

                    xmlRoot.AppendChild(xmlSon);
                }
                else
                {
                    xml.Load(xmlPath);

                    string xp = "//item[@id='1']";

                    XmlElement xmlRoot = xml.DocumentElement;//取得文档的根节点
                    XmlNode xn = xmlRoot.SelectSingleNode(xp);


                  
                    xn["Gold"].InnerText = strGoldMoney;

                    xn["Silver"].InnerText = strSilverMoney;

                    xn["Jade"].InnerText = strJadeMoney;
                    xml.Save(xmlPath);
                }

                try
                {
                    xml.Save(xmlPath);
                    CommonManager.Web.RegJs(this, "alert('修改成功！');location.href=location.href;", false);

                }
                catch (Exception ex)
                {
                    CommonManager.Web.RegJs(this, "alert('修改失败！" + ex.Message + "')", false);
                }
        }

    }
 
