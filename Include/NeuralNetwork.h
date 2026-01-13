#pragma once
#include "LinkedList.h"
#include "Array.h"
#include <stdexcept>
namespace AxionForge {

	class Tensor {
		Array<float> m_data;
		Array<size_t> m_shape;
		Array<size_t> m_stride;
	public:

		Tensor(float data) : m_data{ data }, m_shape{}, m_stride{} {}

		Tensor(const Array<float>& data) : m_data(data), m_shape{ (size_t)data.Length() }, m_stride{ 1 } {}
		Tensor(const Array<Array<float>>& data) : m_shape{ data.Length(), data[0].Length() }, m_stride{data[0].Length(),1} {
			size_t expectedcolumns = data[0].Length();
			for (size_t i = 0; i < data.Length(); i++) {
				if (data[i].Length() != expectedcolumns) {
					throw std::invalid_argument("All rows must have the same number of columns.");
				}
			}

			for (size_t i = 0; i < data.Length(); i++)
				for (size_t j = 0; j < data[i].Length(); j++)
					m_data.Add(data[i][j]);
		}

		const float& item() const {
			return m_data[0];
		}
		float& item() {
			return m_data[0];
		}
		const float& operator()(size_t i) const {
			return m_data[i];
		}
		float& operator()(size_t i) {
			return m_data[i];
		}
		const float& operator()(size_t i, size_t j) const {
			return m_data[i * m_stride[0] + j * m_stride[1]];
		}
		float& operator()(size_t i, size_t j) {
			return m_data[i * m_stride[0] + j * m_stride[1]];
		}

	};

	class NeuronNode {
	public:
		

	};


	class NeuralNetwork {
	public:
		
	};

}