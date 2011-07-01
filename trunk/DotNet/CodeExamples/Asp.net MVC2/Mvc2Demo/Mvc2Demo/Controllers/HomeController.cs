﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Configuration;

namespace Mvc2Demo.Controllers
{
    [HandleError]
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            string aa = ConfigurationManager.AppSettings.Get("myconfig");
            ViewData["Message"] = "欢迎使用 ASP.NET MVC!" + aa;
            return View();
        }

        public ActionResult About()
        {
            return View();
        }
    }
}
