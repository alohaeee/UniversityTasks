var navigator = window.navigator;


var appName = document.createElement("div");
var appCodeName = document.createElement("div");
var appVersion = document.createElement("div");
var userAgent = document.createElement("div");
var browserLanguage = document.createElement("div");
var cookieEnabled = document.createElement("div");

appName.innerHTML = "Browser name: " + navigator.appName;
appCodeName.innerHTML = "Code name: " + navigator.appCodeName;
appVersion.innerHTML = "Version: " + navigator.appVersion;
userAgent.innerHTML = "User agent: " + navigator.userAgent;
browserLanguage.innerHTML = "Language: " + navigator.language;
cookieEnabled.innerHTML = "Coockie enabled: " + navigator.cookieEnabled;

document.body.appendChild(appName);
document.body.appendChild(appCodeName);
document.body.appendChild(appVersion);
document.body.appendChild(userAgent);
document.body.appendChild(browserLanguage);
document.body.appendChild(cookieEnabled);
