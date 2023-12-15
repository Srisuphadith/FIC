-- phpMyAdmin SQL Dump
-- version 5.0.4
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Dec 15, 2023 at 12:50 PM
-- Server version: 10.4.17-MariaDB
-- PHP Version: 7.3.26

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `FIC`
--

-- --------------------------------------------------------

--
-- Table structure for table `Sensor_data`
--

CREATE TABLE `Sensor_data` (
  `id` int(11) NOT NULL,
  `Temperature` float NOT NULL,
  `Humidity` float NOT NULL,
  `Soil_humidity` float NOT NULL,
  `time_stamp` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `Sensor_data`
--

INSERT INTO `Sensor_data` (`id`, `Temperature`, `Humidity`, `Soil_humidity`, `time_stamp`) VALUES
(502, 32.8, 77, 1, '2023-12-02 15:11:42'),
(503, 33.3, 76, 1, '2023-12-02 15:12:13'),
(504, 33.3, 75, 1, '2023-12-02 15:12:45'),
(505, 33.4, 74, 1, '2023-12-02 15:13:16'),
(506, 33.3, 74, 1, '2023-12-02 15:14:29'),
(507, 33.3, 74, 1, '2023-12-02 15:15:04'),
(508, 33.3, 74, 1, '2023-12-02 15:15:41'),
(509, 33.3, 74, 1, '2023-12-02 15:16:17'),
(510, 33.3, 74, 1, '2023-12-02 15:17:01'),
(511, 33.3, 74, 1, '2023-12-02 15:17:39'),
(512, 33.3, 74, 1, '2023-12-02 15:18:15'),
(513, 33.3, 74, 1, '2023-12-02 15:18:55'),
(514, 33.3, 74, 1, '2023-12-02 15:19:32'),
(515, 33.3, 75, 1, '2023-12-02 15:20:08'),
(516, 33.3, 75, 1, '2023-12-02 15:20:42'),
(517, 33.3, 75, 1, '2023-12-02 15:21:18'),
(518, 33.3, 75, 1, '2023-12-02 15:21:54'),
(519, 33.3, 75, 1, '2023-12-02 15:22:30'),
(520, 33, 75, 1, '2023-12-02 15:23:06'),
(521, 37.4, 90, 1, '2023-12-02 15:23:43'),
(522, 34.7, 91, 1, '2023-12-02 15:24:20'),
(523, 33.8, 87, 1, '2023-12-02 15:24:57'),
(524, 33.3, 79, 1, '2023-12-02 15:26:09'),
(525, 32.8, 79, 1, '2023-12-02 15:26:46'),
(526, 32.8, 78, 1, '2023-12-02 15:27:21'),
(527, 32.8, 78, 1, '2023-12-02 15:27:55'),
(528, 32.8, 78, 1, '2023-12-02 15:28:30'),
(529, 33.3, 77, 1, '2023-12-02 15:29:04'),
(530, 33.3, 76, 1, '2023-12-02 15:30:49'),
(531, 33.3, 76, 1, '2023-12-02 15:31:25');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `Sensor_data`
--
ALTER TABLE `Sensor_data`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `Sensor_data`
--
ALTER TABLE `Sensor_data`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=532;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
