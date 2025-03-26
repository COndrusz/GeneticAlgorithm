import re
import graphviz
import os


def read_output_file(file_path):
    """
    Reads and parses the output file to extract the input vector, performance, recovery, and grade.

    Parameters:
    file_path (str): The path to the output file.

    Returns:
    tuple: A tuple containing the input vector (list of ints), performance (float),\
          recovery (float), and grade (float).

    Raises:
    ValueError: If the length of the input vector is not of the form 3n + 1.
    """
    with open(file_path, "r") as file:
        content = file.read()

    vector = list(map(int, re.findall(r"Input vector: (.+)", content)[0].split()))
    performance = float(re.findall(r"Performance: ([\d\.]+)", content)[0])
    recovery = float(re.findall(r"Recovery: ([\d\.]+)", content)[0])
    grade = float(re.findall(r"Grade: ([\d\.]+)", content)[0])

    if len(vector) % 3 != 1:
        raise ValueError("The input vector length must be of the form 3n + 1.")

    return vector, performance, recovery, grade


def create_graph(vector, performance, recovery, grade, output_folder):
    """
    Creates a graph visualization of the input vector and saves it as a PDF file.

    Parameters:
    vector (list of int): The input vector representing the connections in the circuit.
    performance (float): The performance metric of the circuit.
    recovery (float): The recovery metric of the circuit.
    grade (float): The grade metric of the circuit.
    output_folder (str): The folder where the output PDF file will be saved.

    Returns:
    None
    """
    # Ensure the output directory exists
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    # Calculate the number of nodes
    n = len(vector) // 3 - 1

    # Create a new Digraph
    dot = graphviz.Digraph()

    # Set the graph to left to right layout with optimized spacing
    dot.attr(rankdir="LR", nodesep="0.5", ranksep="1")

    # Define node names and properties
    node_names = {0: "Unit 0"}
    for i in range(1, n + 1):
        node_names[i] = f"Unit {i}"
    node_names[n + 1] = "Concentrate"
    node_names[n + 2] = "Tailings"

    # Add subgraph for the leftmost rank (feed node)
    with dot.subgraph() as s:
        s.attr(rank="same")
        s.node(
            "feed",
            "Feed",
            shape="box",
            style="filled",
            color="lightyellow",
            fontsize="20",
            fontname="Arial",
            width="2",
            height="1.5",
        )

    # Add subgraph for the rightmost rank (concentrate and tailings nodes)
    with dot.subgraph() as s:
        s.attr(rank="same")
        s.node(
            str(n + 1),
            "Concentrate",
            shape="box",
            style="filled",
            color="lightgreen",
            fontsize="20",
            fontname="Arial",
            width="2",
            height="1.5",
        )
        s.node(
            str(n + 2),
            "Tailings",
            shape="box",
            style="filled",
            color="lightgrey",
            fontsize="20",
            fontname="Arial",
            width="2",
            height="1.5",
        )

    # Add other nodes to the graph with square shape and styling
    for node, name in node_names.items():
        if name not in ["Concentrate", "Tailings"]:
            dot.node(
                str(node),
                name,
                shape="box",
                style="filled",
                color="lightblue",
                fontsize="20",
                fontname="Arial",
                width="1.5",
                height="1.2",
            )

    # Connect the feed node to the first node in the vector
    dot.edge("feed", f"{vector[0]}:w", color="black", penwidth="1.5")

    # Define edge colors and port positions
    edge_colors = ["blue", "purple", "red"]
    edge_ports = ["n", "e", "s"]  # north (top), east (middle/front), south (bottom)

    # Add edges to the graph
    for i in range(n + 1):  # includes 'Concentrate' and 'Tailings'
        edges = [(i, vector[3 * i + 1]), (i, vector[3 * i + 2]), (i, vector[3 * i + 3])]
        for j, (source, target) in enumerate(edges):
            color = edge_colors[j % 3]
            source_port = edge_ports[j % 3]
            dot.edge(
                f"{source}:{source_port}", f"{target}:w", color=color, penwidth="2"
            )

    # Add performance, recovery, and grade as labels
    label_text = f"Vector: {vector}\nPerformance: {performance}\nRecovery: {recovery}\nGrade: {grade}"
    dot.attr(
        label=label_text, fontsize="30", labelloc="b", fontname="Arial", margin="0.5"
    )

    # Render and display the graph
    output_path = os.path.join(output_folder, "circuit")
    dot.render(output_path, format="pdf")
    print(f"Graph has been saved to {output_path}.pdf")


if __name__ == "__main__":
    # Example usage
    file_path = "output.txt"
    output_folder = "circuit_diagram"
    vector, performance, recovery, grade = read_output_file(file_path)
    create_graph(vector, performance, recovery, grade, output_folder)
