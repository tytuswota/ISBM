-- phpMyAdmin SQL Dump
-- version 4.6.6deb4+deb9u2
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Nov 08, 2020 at 04:08 PM
-- Server version: 10.1.47-MariaDB-0+deb9u1
-- PHP Version: 7.0.33-0+deb9u10

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `boat_data`
--

-- --------------------------------------------------------

--
-- Table structure for table `battery_status`
--

CREATE TABLE `battery_status` (
  `id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `boat_status`
--

CREATE TABLE `boat_status` (
  `course` int(11) NOT NULL,
  `speed` int(11) NOT NULL,
  `date_time` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- --------------------------------------------------------

--
-- Table structure for table `gps`
--

CREATE TABLE `gps` (
  `id` int(11) NOT NULL,
  `longitude` double NOT NULL,
  `latitude` double NOT NULL,
  `date_time` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- Dumping data for table `gps`
--

INSERT INTO `gps` (`id`, `longitude`, `latitude`, `date_time`) VALUES
(1, 51.84342795, 4.335329596057278, '2020-10-25 22:27:59'),
(2, 51.84342795, 4.335329596057278, '2020-10-25 22:33:45'),
(3, 52.2002549, 5.269143393313942, '2020-10-25 22:35:25'),
(4, 51.9172185, 4.4840498, '2020-10-25 22:36:34'),
(5, 51.9172185, 4.4840498, '2020-10-26 12:07:48'),
(6, 51.9172185, 4.4840498, '2020-10-26 12:45:29'),
(7, 51.9172185, 4.4840498, '2020-10-27 09:54:15'),
(8, 51.9172185, 4.4840498, '2020-10-27 10:14:21');

-- --------------------------------------------------------

--
-- Table structure for table `log`
--

CREATE TABLE `log` (
  `id` int(11) NOT NULL,
  `data` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `log`
--

INSERT INTO `log` (`id`, `data`) VALUES
(1, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=873&transmit_time=20-10-25%2021%3A34%3A08&iridium_latitude=58.7137&iridium_longitude=85.2043&iridium_cep=55.0&data=48656c6c6f21205468697320697320612074657374206d6573736167652066726f6d20526f636'),
(2, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=223&transmit_time=20-10-25%2021%3A34%3A09&iridium_latitude=30.6960&iridium_longitude=176.6868&iridium_cep=125.0&data=546865726520617265203130207479706573206f662070656f706c652077686f20756e64657'),
(3, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=645&transmit_time=20-10-25%2021%3A34%3A10&iridium_latitude=7.3179&iridium_longitude=97.6737&iridium_cep=57.0&data=48656c6c6f21205468697320697320612074657374206d6573736167652066726f6d20526f636b'),
(4, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=689&transmit_time=20-10-25%2021%3A34%3A10&iridium_latitude=44.1387&iridium_longitude=8.8208&iridium_cep=26.0&data=4f6e6520736d616c6c207374657020666f722061206d616e206f6e65206769616e74206c656170'),
(5, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=168&transmit_time=20-10-25%2021%3A34%3A09&iridium_latitude=64.3603&iridium_longitude=125.8773&iridium_cep=16.0&data=48656c6c6f21205468697320697320612074657374206d6573736167652066726f6d20526f63'),
(6, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=627&transmit_time=20-10-25%2021%3A34%3A10&iridium_latitude=19.3343&iridium_longitude=119.9146&iridium_cep=57.0&data=546865726520617265203130207479706573206f662070656f706c652077686f20756e646572'),
(7, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=515&transmit_time=20-10-25%2021%3A35%3A00&iridium_latitude=74.9595&iridium_longitude=105.1725&iridium_cep=67.0&data=48656c6c6f21205468697320697320612074657374206d6573736167652066726f6d20526f63'),
(8, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=329&transmit_time=20-10-25%2021%3A35%3A01&iridium_latitude=37.2940&iridium_longitude=61.6531&iridium_cep=27.0&data=48656c6c6f21205468697320697320612074657374206d6573736167652066726f6d20526f636'),
(9, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=689&transmit_time=20-10-25%2021%3A35%3A01&iridium_latitude=45.9411&iridium_longitude=131.8583&iridium_cep=46.0&data=4162636465666768696a6b6c6d6e6f707172737475767778797a31323334353637383930'),
(10, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=880&transmit_time=20-10-25%2021%3A35%3A01&iridium_latitude=42.3882&iridium_longitude=150.8971&iridium_cep=69.0&data=546865726520617265203130207479706573206f662070656f706c652077686f20756e646572'),
(11, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=34&transmit_time=20-10-26%2011%3A11%3A04&iridium_latitude=54.0369&iridium_longitude=80.4748&iridium_cep=119.0&data=546865726520617265203130207479706573206f662070656f706c652077686f20756e6465727'),
(12, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=732&transmit_time=20-10-26%2011%3A46%3A42&iridium_latitude=79.2550&iridium_longitude=83.6652&iridium_cep=36.0&data=4162636465666768696a6b6c6d6e6f707172737475767778797a31323334353637383930'),
(13, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=993&transmit_time=20-10-26%2011%3A46%3A44&iridium_latitude=37.2031&iridium_longitude=136.8079&iridium_cep=120.0&data=4f6e6520736d616c6c207374657020666f722061206d616e206f6e65206769616e74206c656'),
(14, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=300&transmit_time=20-10-26%2011%3A46%3A44&iridium_latitude=12.7717&iridium_longitude=178.6826&iridium_cep=97.0&data=48656c6c6f21205468697320697320612074657374206d6573736167652066726f6d20526f63'),
(15, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=409&transmit_time=20-10-26%2011%3A46%3A44&iridium_latitude=25.7888&iridium_longitude=144.7282&iridium_cep=109.0&data=4162636465666768696a6b6c6d6e6f707172737475767778797a31323334353637383930'),
(16, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=454&transmit_time=20-10-26%2011%3A46%3A44&iridium_latitude=26.8033&iridium_longitude=155.3022&iridium_cep=52.0&data=48656c6c6f21205468697320697320612074657374206d6573736167652066726f6d20526f63'),
(17, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=73&transmit_time=20-10-26%2011%3A46%3A44&iridium_latitude=19.7614&iridium_longitude=10.6878&iridium_cep=56.0&data=48656c6c6f21205468697320697320612074657374206d6573736167652066726f6d20526f636b'),
(18, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=427&transmit_time=20-10-26%2011%3A46%3A45&iridium_latitude=69.7184&iridium_longitude=151.3161&iridium_cep=1.0&data=546865726520617265203130207479706573206f662070656f706c652077686f20756e6465727'),
(19, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=658&transmit_time=20-10-26%2011%3A46%3A45&iridium_latitude=0.5152&iridium_longitude=83.8086&iridium_cep=43.0&data=4f6e6520736d616c6c207374657020666f722061206d616e206f6e65206769616e74206c656170'),
(20, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=276&transmit_time=20-10-26%2011%3A46%3A45&iridium_latitude=66.8937&iridium_longitude=10.9243&iridium_cep=11.0&data=546865726520617265203130207479706573206f662070656f706c652077686f20756e6465727'),
(21, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=548&transmit_time=20-10-26%2011%3A46%3A45&iridium_latitude=22.8536&iridium_longitude=98.2848&iridium_cep=115.0&data=48656c6c6f21205468697320697320612074657374206d6573736167652066726f6d20526f63'),
(22, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=881&transmit_time=20-10-26%2011%3A46%3A45&iridium_latitude=37.7253&iridium_longitude=167.3927&iridium_cep=68.0&data=546865726520617265203130207479706573206f662070656f706c652077686f20756e646572'),
(23, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=872&transmit_time=20-10-26%2011%3A46%3A46&iridium_latitude=57.2670&iridium_longitude=50.4438&iridium_cep=3.0&data=546865726520617265203130207479706573206f662070656f706c652077686f20756e64657273'),
(24, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=372&transmit_time=20-10-26%2011%3A46%3A45&iridium_latitude=5.7723&iridium_longitude=10.8582&iridium_cep=124.0&data=4162636465666768696a6b6c6d6e6f707172737475767778797a31323334353637383930'),
(25, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=204&transmit_time=20-10-26%2011%3A46%3A46&iridium_latitude=46.0845&iridium_longitude=21.1294&iridium_cep=25.0&data=546865726520617265203130207479706573206f662070656f706c652077686f20756e6465727'),
(26, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=22&transmit_time=20-10-26%2011%3A46%3A46&iridium_latitude=4.6852&iridium_longitude=72.5054&iridium_cep=36.0&data=546865726520617265203130207479706573206f662070656f706c652077686f20756e646572737'),
(27, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=98&transmit_time=20-10-26%2011%3A46%3A46&iridium_latitude=72.3174&iridium_longitude=115.9169&iridium_cep=6.0&data=48656c6c6f21205468697320697320612074657374206d6573736167652066726f6d20526f636b'),
(28, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=632&transmit_time=20-10-26%2011%3A46%3A46&iridium_latitude=0.9539&iridium_longitude=10.9604&iridium_cep=72.0&data=4162636465666768696a6b6c6d6e6f707172737475767778797a31323334353637383930'),
(29, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=589&transmit_time=20-10-26%2011%3A46%3A46&iridium_latitude=3.6346&iridium_longitude=119.1827&iridium_cep=70.0&data=48656c6c6f21205468697320697320612074657374206d6573736167652066726f6d20526f636'),
(30, '{\"emei\":\"30043406443470\",\"momsn\":\"14\",\"transmition_time\":\"\",\"data\":\"00\"}'),
(31, '{\"emei\":\"30043406443470\",\"momsn\":\"14\",\"transmition_time\":\"\",\"data\":\"00\"}'),
(32, '0x%5B%5D=androxgh0st'),
(33, 'imei=300434064434370&device_type=ROCKBLOCK&serial=200842&momsn=258&transmit_time=20-10-29%2009%3A37%3A55&iridium_latitude=68.8990&iridium_longitude=12.2632&iridium_cep=23.0&data=4f6e6520736d616c6c207374657020666f722061206d616e206f6e65206769616e74206c65617'),
(34, '0x%5B%5D=androxgh0st'),
(35, '0x%5B%5D=androxgh0st'),
(36, '_method=__construct&filter[]=system&method=get&server[REQUEST_METHOD]=uname&ipconfig'),
(37, '_method=__construct&filter[]=system&method=get&server[REQUEST_METHOD]=uname&ipconfig'),
(38, 'epass=2dmfrb28nu3c6s9j&routestring=ajax/render/widget_php&widgetConfig[code]=die(@md5(HellovBulletin));'),
(39, '%5f%6d%65%74%68%6f%64=%5f%5f%63%6f%6e%73%74%72%75%63%74&%66%69%6c%74%65%72%5b%5d=%61%73%73%65%72%74&%73%65%72%76%65%72%5b%52%45%51%55%45%53%54%5f%4d%45%54%48%4f%44%5d=die(md5(DIRECTORY_SEPARATOR))'),
(40, '[]=[]'),
(41, 'epass=2dmfrb28nu3c6s9j&routestring=ajax/render/widget_php&widgetConfig[code]=die(@md5(HellovBulletin));'),
(42, '%5f%6d%65%74%68%6f%64=%5f%5f%63%6f%6e%73%74%72%75%63%74&%66%69%6c%74%65%72%5b%5d=%61%73%73%65%72%74&%73%65%72%76%65%72%5b%52%45%51%55%45%53%54%5f%4d%45%54%48%4f%44%5d=die(md5(DIRECTORY_SEPARATOR))'),
(43, '0x%5B%5D=anarchy99'),
(44, '_method=__construct&filter[]=system&method=get&server[REQUEST_METHOD]=uname&ipconfig'),
(45, '0x%5B%5D=androxgh0st'),
(46, '0x%5B%5D=androxgh0st'),
(47, 'epass=2dmfrb28nu3c6s9j&routestring=ajax/render/widget_php&widgetConfig[code]=die(@md5(HellovBulletin));'),
(48, '%5f%6d%65%74%68%6f%64=%5f%5f%63%6f%6e%73%74%72%75%63%74&%66%69%6c%74%65%72%5b%5d=%61%73%73%65%72%74&%73%65%72%76%65%72%5b%52%45%51%55%45%53%54%5f%4d%45%54%48%4f%44%5d=die(md5(DIRECTORY_SEPARATOR))'),
(49, '0x%5B%5D=androxgh0st'),
(50, '_method=__construct&filter[]=system&method=get&server[REQUEST_METHOD]=uname&ipconfig');

-- --------------------------------------------------------

--
-- Table structure for table `sensor_status`
--

CREATE TABLE `sensor_status` (
  `id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `battery_status`
--
ALTER TABLE `battery_status`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `gps`
--
ALTER TABLE `gps`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `log`
--
ALTER TABLE `log`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `sensor_status`
--
ALTER TABLE `sensor_status`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `battery_status`
--
ALTER TABLE `battery_status`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `gps`
--
ALTER TABLE `gps`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;
--
-- AUTO_INCREMENT for table `log`
--
ALTER TABLE `log`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=51;
--
-- AUTO_INCREMENT for table `sensor_status`
--
ALTER TABLE `sensor_status`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
