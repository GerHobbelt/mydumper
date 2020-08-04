Name:           mydumper
Version:        0.9.55
Release:        1%{?dist}
Summary:        A high-performance MySQL backup tool

Group:          Applications/Databases
License:        GPLv3+
URL:            https://github.com/peak/mydumper
Source0:        %{url}/archive/v%{version}.tar.gz

BuildRequires:  glib2-devel zlib-devel pcre-devel openssl-devel gcc-c++
BuildRequires:  cmake make
BuildRequires:  Percona-Server-devel-57

%description
This package provides mydumper and myloader MySQL backup tools.

mydumper is a tool used for backing up MySQL database servers much
faster than the mysqldump tool distributed with MySQL. The advantages
of mydumper are: parallelism, easier to manage output, consistency,
manageability.

myloader is a tool used for multi-threaded restoration of mydumper backups.


%prep
%setup -q

%build

%cmake . -DMYSQL_LIBRARIES_mysqlclient:FILEPATH=/usr/lib64/mysql/libmysqlclient.a

%make_build

%install
%make_install

%files
%defattr(-,root,root,-)
%{_bindir}/mydumper
%{_bindir}/myloader